#include <flecs.h>
#include <cstdint>
#include <string>

namespace engine::config2 {
  namespace detail {
    template<std::size_t Size>
    class TemplatedString {
    public:
      constexpr TemplatedString(const char (&str)[Size]) {
        for (std::size_t i = 0; i < Size; ++i) {
          value[i] = str[i];
        }
        value[Size] = 0; //for uses as c-string
      }
      char value[Size+1];
    };

    template<class T>
    struct TemplatedToStringFunc {
      using FuncType = std::size_t (*)(char*, const std::size_t, const T&);
      constexpr TemplatedToStringFunc(FuncType f): f(f) {}
      FuncType f;
    };

    template <class Type, TemplatedString TypeName, TemplatedToStringFunc ToStringFunc>
    struct TypedValue {
      static inline const char* type_name() {
        return TypeName.value;
      }

      inline TypedValue(Type&& value): value(std::move(value)) {}  
      inline std::size_t to_string(char* buff, const std::size_t buff_size) {
        return ToStringFunc.f(buff, buff_size, value);
      }
      //inline 
      Type value;
    };

    template<class T>
    std::size_t testfunc(char* buff, const std::size_t size, const T& value) {return 0;}

  } //namespace detail

  namespace type {
    using Int32 = detail::TypedValue<std::int32_t, "int32", detail::testfunc<std::int32_t>>;
    using Uint32 = detail::TypedValue<std::uint32_t, "uint32", detail::testfunc<std::uint32_t>>;
    using Bool = detail::TypedValue<bool, "bool", detail::testfunc<bool>>;
    using Float = detail::TypedValue<float, "float", detail::testfunc<float>>;
    //using String = detail::TypedValue<std::string, "string", detail::testfunc<std::string>>;
  } //namespace type

  template <class T>
  void create_var(flecs::world& world, const char* name, T&& data);


  void keks() {
    flecs::world world;
    create_var<std::uint64_t>(world, "123", 123);
  }


} //namespace engine::config2