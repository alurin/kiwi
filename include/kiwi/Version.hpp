#ifndef KIWI_VERSION_INCLUDED
#define KIWI_VERSION_INCLUDED

namespace kiwi
{
    class Version
    {
    public:
        enum VersionType {
            VERSION_DEV     = 1,
            VERSION_ALPHA   = 2,
            VERSION_BETA    = 3,
            VERSION_RC      = 4,
            VERSION_PROD    = 5,
        };

        Version() : m_major(0), m_minor(1), m_revision(0), m_type(VERSION_DEV) {}

        Version(int32_t major, int32_t minor = 0, int32_t revision = 0, type = VERSION_PROD)
            : m_major(major), m_minor(minor), m_revision(revision), m_type(type) {}

        /// Returns major number for version
        int32_t getMajor() const {
            return m_major;
        }

        /// Returns minor number for version
        int32_t getMinor() const {
            return m_minor;
        }

        /// Returns revision number for version
        int32_t getRevision() const {
            return m_revision;
        }

        /// Returns type number for version
        VersionType getType() const {
            return m_type;
        }

    protected:
        int32_t m_major;
        int32_t m_minor;
        int32_t m_revision;
        VersionType m_type;
    };
}

#endif