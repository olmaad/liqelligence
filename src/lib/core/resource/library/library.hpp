#pragma once

#include <core/resource/library/resource_library.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace liqelligence::core::resource
{
    class base_library;

    class library
    {
    public:
        void reset();

        template<typename t_library>
        static t_library& get()
        {
            auto& libraries = instance()._libraries;

            std::type_index id = typeid(t_library);

            auto library_it = libraries.find(id);
            if (library_it == libraries.end()) {
                auto library = std::make_shared<t_library>();
                libraries.emplace(id, library);

                return *library;
            }
            else {
                return static_cast<t_library&>(*library_it->second);
            }
        }

    private:
        static library& instance();

    private:
        std::unordered_map<std::type_index, std::shared_ptr<base_library>> _libraries;
    };
}
