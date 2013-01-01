/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "AddressMap.hpp"
#include "DynamicTable.cpp"

using namespace kiwi;

namespace {
    /// New Fields listeners
    class FieldInsert {
    public:
        /// constructor
        FieldInsert(StaticAddressMap* amap);

        /// handler
        void operator()(FieldPtr Field);
    protected:
        /// amap
        StaticAddressMap* m_amap;
    };

    /// Override Fields listeners
    class FieldOverride {
    public:
        /// constructor
        FieldOverride(UpcastAddressMap* amap);

        /// handler
        void operator()(FieldPtr Field, FieldPtr inherit);
    protected:
        /// amap
        UpcastAddressMap* m_amap;
    };
}

AddressMap::AddressMap(TypePtr type, ModulePtr module)
: m_type(type), m_module(module), m_dtable(module) {

}

AddressMap::~AddressMap()
{ }

FieldInsert::FieldInsert(StaticAddressMap* amap)
: m_amap(amap) {
}

FieldOverride::FieldOverride(UpcastAddressMap* amap)
: m_amap(amap) {
}

// constructor
StaticAddressMap::StaticAddressMap(TypePtr owner)
: AddressMap(owner, owner->getModule()) {
    TypeImpl* meta = owner->getMetadata();
    meta->getFields().onInsert.connect(FieldInsert(this));
}

// constructor
UpcastAddressMap::UpcastAddressMap(TypePtr ancestor, TypePtr derived)
: AddressMap(ancestor, derived->getModule()), m_derived(derived) {
    TypeImpl* meta = derived->getMetadata();
    meta->getFields().onOverride.connect(FieldOverride(this));
}

llvm::GlobalVariable* AddressMap::getBackendVariable() const {
    return m_dtable.getBackendVariable();
}

void* AddressMap::getNativePointer() const {
    return m_dtable.getNativePointer();
}

/// returns size of address map
size_t AddressMap::size() const {
    return m_dtable.size();
}

/// insert Field in amap
void StaticAddressMap::insertSlot(FieldPtr field) {
    if (field->m_position == -1) { // guard from recursion
        field->m_position = m_dtable.nextPosition();
    }
}

void AddressMap::update() {
    llvm::Module*       module = getModule()->getMetadata()->getBackendModule();
    llvm::LLVMContext& context = module->getContext();

    MemberSet<Field>& fields = getType()->getMetadata()->getFields();
    if (fields.size() == 0) {
        return;
    }

    // Create layout type
    std::vector<llvm::Type*> elements;
    elements.push_back(llvm::IntegerType::get(context, 8)->getPointerTo());
    for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i) {
        FieldPtr field = *i;
        elements.push_back(field->getFieldType()->getMetadata()->getBackendVariableType());
    }
    llvm::StructType* layoutType = llvm::StructType::get(context, elements, false);

    // Populate offsets
    std::vector<llvm::Constant*> positions(fields.size(), 0);
    computeLayoutOffsets(layoutType, positions);

    // Compute offset with JIT
    llvm::Type* offsetType    = llvm::IntegerType::get(context, 64);
    llvm::ArrayType* amapType = llvm::ArrayType::get(offsetType, positions.size());
    llvm::Constant* amapValue = llvm::ConstantArray::get(amapType, positions);

    // map table to pointer
    m_dtable.resize(positions.size());
    kiwi_assert(m_dtable.get(), "AMap is not nullable");
    ContextImpl* meta             = getType()->getContext()->getMetadata();
    llvm::ExecutionEngine* engine = meta->getBackendEngine();
    engine->InitializeMemory(amapValue, m_dtable.get());
}

// compute layout offset
void StaticAddressMap::computeLayoutOffsets(
    llvm::StructType* layoutType,
    std::vector<llvm::Constant*>& positions
) {
    int j = 0;
    MemberSet<Field>& fields = getType()->getMetadata()->getFields();
    for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i, ++j) {
        FieldPtr field = *i;
        int32_t pos    = field->getPosition();
        kiwi_assert(pos != -1, "Position is -1 in compute layout offsets");
        positions[pos] = llvm::ConstantExpr::getOffsetOf(layoutType, j + 1);
    }
}
// compute layout offset
void UpcastAddressMap::computeLayoutOffsets(
    llvm::StructType* layoutType,
    std::vector<llvm::Constant*>& positions
) {
    MemberSet<Field>& fields    = getType()->getMetadata()->getFields();
    MemberSet<Field>& overrides = getDerivedType()->getMetadata()->getFields();
    int j = 0;
    for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i, ++j) {
        FieldPtr field    = *i;
        FieldPtr override = overrides.find(field);
        int32_t pos       = field->getPosition();

        kiwi_assert(override,  "Overridable field not found");
        kiwi_assert(pos != -1, "Position is -1 in compute layout offsets");
        positions[pos] = llvm::ConstantExpr::getOffsetOf(layoutType, j + 1);
    }
}

// handler
void FieldInsert::operator()(FieldPtr Field) {
    m_amap->update();
}

// handler
// @todo testes
void FieldOverride::operator()(FieldPtr Field, FieldPtr inherit) {
    if (inherit->getOwnerType() == m_amap->getType()) {
        m_amap->update();
    }
}
