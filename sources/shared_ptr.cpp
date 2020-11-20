// Copyright 2020 Alexander <scorpy2013>

#include "shared_ptr.hpp"
template <typename T>
SharedPtr<T>::SharedPtr() {
  reference = nullptr;
  reference_count = nullptr;
}
template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
  reference = ptr;
  reference_count = new std::atomic_uint{1};
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  reference = r.reference;
  reference_count = r.reference_count;
  (*reference_count)++;
}
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) noexcept {
  reference = r.reference;
  reference_count = r.reference_count;
  r.reference = nullptr;
  r.reference_count = nullptr;
}
template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (!reference_count) return;
  if (--(*reference_count) == 0) {
    delete reference;
    delete reference_count;
  }
}
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  if (this == &r) {
    return *this;
  }
  //!!!!!!!!!!!!!!!!!!!!
  this->~SharedPtr();
  reference = r.reference;
  reference_count = r.reference_count;
  return *this;
}
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr& {
  if (this == &r) {
    return *this;
  }
  //!!!!!!!!!!!!!!!!!!!!
  this->~SharedPtr();
  reference = r.reference;
  reference_count = r.reference_count;
  r.reference = nullptr;
  r.reference_count = nullptr;
  return *this;
}

// проверяет, указывает ли указатель на объект
template <typename T>
SharedPtr<T>::operator bool() const {
  return reference != nullptr;
}
template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *reference;
}
template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return reference;
}

template <typename T>
auto SharedPtr<T>::get() -> T* {
  return reference;
}
template <typename T>
void SharedPtr<T>::reset() {
  *this = std::move(SharedPtr());
}
template <typename T>
void SharedPtr<T>::reset(T* ptr) {
  *this = std::move(SharedPtr<T>(ptr));
}
template <typename T>
void SharedPtr<T>::swap(SharedPtr& r) {
  std::swap(reference, r.reference);
  std::swap(reference_count, r.reference_count);
}
// возвращает количество объектов SharedPtr, которые ссылаются на тот же
// управляемый объект
template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return static_cast<size_t>(*reference);
}
