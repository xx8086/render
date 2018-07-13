//
//  object.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include "ref_counted.hpp"
#include "string_hash.hpp"
#include "base_type.h"
//#include "context.h"

namespace megranate {
    class Context;
    
    class TypeInfo{
    public:
        TypeInfo(const mg_char* type_name, const TypeInfo* base_type_info);
        ~TypeInfo();
        
    public:
        mg_bool is_type_of(StringHash type) const;
        mg_bool is_type_of(const TypeInfo* typeInfo) const;
        template<typename T> bool is_type_of() const { return is_type_of(T::get_type_info_static()); }
        
        StringHash get_type() const { return _type; }
        const std::string& get_type_name() const { return _type_name;}
        const TypeInfo* get_base_type_info() const { return _base_type_info; }
        
    private:
        StringHash _type;
        std::string _type_name;
        const TypeInfo* _base_type_info;
    };
    
#define MEGRANATE_OBJECT(typeName, baseTypeName) \
public: \
typedef typeName ClassName; \
typedef baseTypeName BaseClassName; \
virtual megranate::StringHash get_type() const { return get_type_info_static()->get_type(); } \
virtual const std::string& get_type_name() const { return get_type_info_static()->get_type_name(); } \
virtual const megranate::TypeInfo* get_type_info() const { return get_type_info_static(); } \
\
static megranate::StringHash get_type_static() { return get_type_info_static()->get_type(); } \
static const std::string& get_type_name_static() { return get_type_info_static()->get_type_name(); } \
\
static const megranate::TypeInfo* get_type_info_static() { static const megranate::TypeInfo typeInfoStatic(#typeName, BaseClassName::get_type_info_static()); return &typeInfoStatic; } 

    
    class Object : public RefCounted{
    public:
        Object(Context* context);
        virtual ~Object();
    public:
        virtual StringHash get_type() const = 0;
        virtual const std::string& get_type_name() const = 0;
        virtual const TypeInfo* get_type_info() const = 0;
        static const TypeInfo* get_type_info_static(){return nullptr;}
        
        mg_bool is_instance_of(StringHash type) const;
        mg_bool is_instance_of(const TypeInfo* type_info) const;
        template<typename T> mg_bool is_instance_of() const { return is_instance_of(T::get_type_info_static()); }
        template <typename T> T* get_sub_system() const;
        
        Context* get_context() const {return _context;}
        Object* get_sub_system(StringHash type) const;
        
    protected:
        Context* _context;
        
    };
    
    template <typename T> T* Object::get_sub_system() const { return static_cast<T*>(get_sub_system(T::get_type_static())); }
    
    class ObjectFactory : public RefCounted{
    public:
        ObjectFactory(Context* context) :
        _context(context){
            //assert(_context);
        }
        
        virtual Object* create_object() = 0;
        Context* get_context() const { return _context; }
        const TypeInfo* get_type_info() const { return _type_info; }
        StringHash get_type() const { return _type_info->get_type(); }
        const std::string& get_type_name() const { return _type_info->get_type_name(); }
    protected:
        Context* _context;
        const TypeInfo* _type_info;
    };
    
    
    template<typename T>
    class ObjectFactoryImpl : public ObjectFactory{
    public:
        ObjectFactoryImpl(Context* context):
        ObjectFactory(context){
            _type_info = T::get_type_info_static();
        }
        virtual Object* create_object() {
            return dynamic_cast<Object*>(new T(_context));
        }
    };
}

#endif /* object_hpp */
