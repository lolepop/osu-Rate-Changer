// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_msg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_msg_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_msg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_msg_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_msg_2eproto;
namespace messaging {
class Msg;
struct MsgDefaultTypeInternal;
extern MsgDefaultTypeInternal _Msg_default_instance_;
}  // namespace messaging
PROTOBUF_NAMESPACE_OPEN
template<> ::messaging::Msg* Arena::CreateMaybeMessage<::messaging::Msg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace messaging {

enum UiMsg : int {
  SETSPEED = 0,
  SETBPMSCALE = 1,
  UiMsg_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  UiMsg_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool UiMsg_IsValid(int value);
constexpr UiMsg UiMsg_MIN = SETSPEED;
constexpr UiMsg UiMsg_MAX = SETBPMSCALE;
constexpr int UiMsg_ARRAYSIZE = UiMsg_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* UiMsg_descriptor();
template<typename T>
inline const std::string& UiMsg_Name(T enum_t_value) {
  static_assert(::std::is_same<T, UiMsg>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function UiMsg_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    UiMsg_descriptor(), enum_t_value);
}
inline bool UiMsg_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, UiMsg* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<UiMsg>(
    UiMsg_descriptor(), name, value);
}
enum DllMsg : int {
  CONNECTED = 0,
  RESPONSE = 1,
  DllMsg_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  DllMsg_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool DllMsg_IsValid(int value);
constexpr DllMsg DllMsg_MIN = CONNECTED;
constexpr DllMsg DllMsg_MAX = RESPONSE;
constexpr int DllMsg_ARRAYSIZE = DllMsg_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* DllMsg_descriptor();
template<typename T>
inline const std::string& DllMsg_Name(T enum_t_value) {
  static_assert(::std::is_same<T, DllMsg>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function DllMsg_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    DllMsg_descriptor(), enum_t_value);
}
inline bool DllMsg_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, DllMsg* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<DllMsg>(
    DllMsg_descriptor(), name, value);
}
// ===================================================================

class Msg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:messaging.Msg) */ {
 public:
  inline Msg() : Msg(nullptr) {}
  ~Msg() override;
  explicit constexpr Msg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Msg(const Msg& from);
  Msg(Msg&& from) noexcept
    : Msg() {
    *this = ::std::move(from);
  }

  inline Msg& operator=(const Msg& from) {
    CopyFrom(from);
    return *this;
  }
  inline Msg& operator=(Msg&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Msg& default_instance() {
    return *internal_default_instance();
  }
  static inline const Msg* internal_default_instance() {
    return reinterpret_cast<const Msg*>(
               &_Msg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Msg& a, Msg& b) {
    a.Swap(&b);
  }
  inline void Swap(Msg* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Msg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Msg* New() const final {
    return new Msg();
  }

  Msg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Msg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Msg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Msg& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Msg* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "messaging.Msg";
  }
  protected:
  explicit Msg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUiMsgFieldNumber = 1,
    kDllMsgFieldNumber = 2,
    kDoubleValFieldNumber = 3,
    kBoolValFieldNumber = 4,
  };
  // .messaging.UiMsg uiMsg = 1;
  void clear_uimsg();
  ::messaging::UiMsg uimsg() const;
  void set_uimsg(::messaging::UiMsg value);
  private:
  ::messaging::UiMsg _internal_uimsg() const;
  void _internal_set_uimsg(::messaging::UiMsg value);
  public:

  // .messaging.DllMsg dllMsg = 2;
  void clear_dllmsg();
  ::messaging::DllMsg dllmsg() const;
  void set_dllmsg(::messaging::DllMsg value);
  private:
  ::messaging::DllMsg _internal_dllmsg() const;
  void _internal_set_dllmsg(::messaging::DllMsg value);
  public:

  // double doubleVal = 3;
  void clear_doubleval();
  double doubleval() const;
  void set_doubleval(double value);
  private:
  double _internal_doubleval() const;
  void _internal_set_doubleval(double value);
  public:

  // bool boolVal = 4;
  void clear_boolval();
  bool boolval() const;
  void set_boolval(bool value);
  private:
  bool _internal_boolval() const;
  void _internal_set_boolval(bool value);
  public:

  // @@protoc_insertion_point(class_scope:messaging.Msg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  int uimsg_;
  int dllmsg_;
  double doubleval_;
  bool boolval_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_msg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Msg

// .messaging.UiMsg uiMsg = 1;
inline void Msg::clear_uimsg() {
  uimsg_ = 0;
}
inline ::messaging::UiMsg Msg::_internal_uimsg() const {
  return static_cast< ::messaging::UiMsg >(uimsg_);
}
inline ::messaging::UiMsg Msg::uimsg() const {
  // @@protoc_insertion_point(field_get:messaging.Msg.uiMsg)
  return _internal_uimsg();
}
inline void Msg::_internal_set_uimsg(::messaging::UiMsg value) {
  
  uimsg_ = value;
}
inline void Msg::set_uimsg(::messaging::UiMsg value) {
  _internal_set_uimsg(value);
  // @@protoc_insertion_point(field_set:messaging.Msg.uiMsg)
}

// .messaging.DllMsg dllMsg = 2;
inline void Msg::clear_dllmsg() {
  dllmsg_ = 0;
}
inline ::messaging::DllMsg Msg::_internal_dllmsg() const {
  return static_cast< ::messaging::DllMsg >(dllmsg_);
}
inline ::messaging::DllMsg Msg::dllmsg() const {
  // @@protoc_insertion_point(field_get:messaging.Msg.dllMsg)
  return _internal_dllmsg();
}
inline void Msg::_internal_set_dllmsg(::messaging::DllMsg value) {
  
  dllmsg_ = value;
}
inline void Msg::set_dllmsg(::messaging::DllMsg value) {
  _internal_set_dllmsg(value);
  // @@protoc_insertion_point(field_set:messaging.Msg.dllMsg)
}

// double doubleVal = 3;
inline void Msg::clear_doubleval() {
  doubleval_ = 0;
}
inline double Msg::_internal_doubleval() const {
  return doubleval_;
}
inline double Msg::doubleval() const {
  // @@protoc_insertion_point(field_get:messaging.Msg.doubleVal)
  return _internal_doubleval();
}
inline void Msg::_internal_set_doubleval(double value) {
  
  doubleval_ = value;
}
inline void Msg::set_doubleval(double value) {
  _internal_set_doubleval(value);
  // @@protoc_insertion_point(field_set:messaging.Msg.doubleVal)
}

// bool boolVal = 4;
inline void Msg::clear_boolval() {
  boolval_ = false;
}
inline bool Msg::_internal_boolval() const {
  return boolval_;
}
inline bool Msg::boolval() const {
  // @@protoc_insertion_point(field_get:messaging.Msg.boolVal)
  return _internal_boolval();
}
inline void Msg::_internal_set_boolval(bool value) {
  
  boolval_ = value;
}
inline void Msg::set_boolval(bool value) {
  _internal_set_boolval(value);
  // @@protoc_insertion_point(field_set:messaging.Msg.boolVal)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace messaging

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::messaging::UiMsg> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::messaging::UiMsg>() {
  return ::messaging::UiMsg_descriptor();
}
template <> struct is_proto_enum< ::messaging::DllMsg> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::messaging::DllMsg>() {
  return ::messaging::DllMsg_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_msg_2eproto
