//
// Purpur Tentakel
// 06.08.24
//

#pragma once

#include <uil/global/exception.hpp>
#include <algorithm>
#include <cpt/vec2.hpp>
#include <memory>
#include <vector>

namespace uil::sys {
    template<class T>
    class BaseManager {
    public:
        using ElementPtr      = std::shared_ptr<T>;
        using ElementPtr_Weak = std::weak_ptr<T>;
        using ElementVector   = std::vector<ElementPtr>;

    private:
        ElementVector m_elements{};

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_element_with_offset(cpt::usize const offset, Args&&... args)
            requires(std::constructible_from<S, Args...>) {
            return emplace_element_with_iterator<S>(m_elements.begin() + static_cast<cpt::i64>(offset),
                                                    std::forward<Args>(args)...);
        }

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_element_with_iterator(typename ElementVector::iterator const& iterator, Args&&... args)
            requires(std::constructible_from<S, Args...>) {
            auto elem            = std::make_shared<S>(std::forward<Args>(args)...);
            std::weak_ptr<S> ptr = elem;
            m_elements.insert(iterator, std::move(elem));
            return ptr;
        }

        ElementPtr_Weak insert_element_with_offset(cpt::usize const offset, ElementPtr element) {
            return insert_element_with_iterator(m_elements.begin() + static_cast<cpt::i64>(offset), std::move(element));
        }

        ElementPtr_Weak insert_element_with_iterator(typename ElementVector::iterator const& iterator,
                                                     ElementPtr element) {
            ElementPtr_Weak ptr = element;
            m_elements.insert(iterator, std::move(element));
            return ptr;
        }

        void erase_with_offset(cpt::usize const offset) {
            erase_with_iterator(m_elements.begin() + static_cast<cpt::i64>(offset));
        }

        void erase_with_iterator(typename ElementVector::iterator const& iterator) {
            m_elements.erase(iterator);
        }

    protected:
        [[nodiscard]] ElementVector elements() const {
            return m_elements;
        }

    public:
        BaseManager() = default;

        virtual ~BaseManager() = default;

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_top(Args&&... args)
            requires(std::constructible_from<S, Args...>) {
            return emplace_element_with_offset<S>(0, std::forward<Args>(args)...);
        }

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_bottom(Args&&... args)
            requires(std::constructible_from<S, Args...>) {
            return emplace_element_with_iterator<S>(m_elements.end(), std::forward<Args>(args)...);
        }


        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_at(cpt::usize const index, Args&&... args)
            requires(std::constructible_from<S, Args...>) {
            if (index > m_elements.size()) {
                throw BadElementIndex("index is out of bounce");
            }
            if (index == m_elements.size()) {
                return emplace_bottom<S>(args...);
            }

            return emplace_emelent_with_offset<S>(index, std::forward<Args>(args)...);
        }

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_before(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<S, Args...>) {
            if (auto const shared_scene = scene.lock(); shared_scene) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&b = shared_scene](auto const& elem) {
                              return elem.get() == b.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find before element in elements vector");
                }

                return emplace_element_with_iterator<S>(iterator, std::forward<Args>(args)...);
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_after(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<S, Args...>) {
            if (auto const shared_scene = scene.lock(); shared_scene) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&a = shared_scene](auto const& elem) {
                              return elem.get() == a.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find after element in elements vector");
                }

                return emplace_element_with_iterator<S>(iterator + 1, std::forward<Args>(args)...);
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        ElementPtr_Weak push_top(ElementPtr to_push) {
            return insert_element_with_offset(0, std::move(to_push));
        }

        ElementPtr_Weak push_bottom(ElementPtr to_push) {
            return insert_element_with_iterator(m_elements.end(), std::move(to_push));
        }

        ElementPtr_Weak push_at(cpt::usize const index, ElementPtr to_push) {
            if (index > m_elements.size()) {
                throw BadElementIndex("index is out of bounce");
            }

            if (index == m_elements.size()) {
                return push_bottom(std::move(to_push));
            }

            return insert_element_with_offset(index, std::move(to_push));
        }

        ElementPtr_Weak push_before(ElementPtr_Weak element, ElementPtr to_push) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&b = shared_element](auto const& elem) {
                              return b.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find before element in elements vector");
                }
                return insert_element_with_iterator(iterator, std::move(to_push));
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        ElementPtr_Weak push_after(ElementPtr_Weak element, ElementPtr to_push) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&a = shared_element](auto const& elem) {
                              return a.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find after element in elements vector");
                }

                return insert_element_with_iterator(iterator + 1, std::move(to_push));
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        ElementPtr pop_top() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }

            auto temp = m_elements.front();
            erase_with_iterator(m_elements.begin());
            return temp;
        }

        ElementPtr pop_bottom() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }

            auto temp = m_elements.back();
            m_elements.pop_back();
            return temp;
        }

        ElementPtr pop_at(cpt::usize const index) {
            if (index >= m_elements.size()) {
                throw BadElementIndex("index out of range while pop at");
            }

            auto temp = m_elements.at(index);
            erase_with_offset(index);
            return temp;
        }

        ElementPtr pop_before(ElementPtr_Weak element) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&b = shared_element](auto const& elem) {
                              return b.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element before in the elements vector");
                }
                if (iterator == m_elements.begin()) {
                    throw BadElementErase("No element before the provided element");
                }
                auto temp = std::move(*(iterator - 1));
                erase_with_iterator(iterator - 1);
                return temp;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        ElementPtr pop_after(ElementPtr_Weak element) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&a = shared_element](auto const& elem) {
                              return a.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element before in the elements vector");
                }
                if (iterator == m_elements.end() - 1) {
                    throw BadElementErase("No element after the provided element");
                }
                auto temp = std::move(*(iterator + 1));
                erase_with_iterator(iterator + 1);
                return temp;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        ElementPtr pop_this(ElementPtr_Weak to_pop) {
            if (auto const shared_to_pop = to_pop.lock(); shared_to_pop) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&d = shared_to_pop](auto const elem) {
                              return d.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element in the elements vector");
                }
                auto temp = std::move(*iterator);
                erase_with_iterator(iterator);
                return temp;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        void erase_top() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }
            erase_with_iterator(m_elements.begin());
        }

        void erase_bottom() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }
            m_elements.pop_back();
        }

        void erase_at(cpt::usize const index) {
            if (index >= m_elements.size()) {
                throw BadElementIndex("index out of range while erasing an element");
            }

            erase_with_offset(index);
        }

        void erase_before(ElementPtr_Weak element) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&b = shared_element](auto const& elem) {
                              return b.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element before in the elements vector");
                }
                if (iterator == m_elements.begin()) {
                    throw BadElementErase("No element before the provided element");
                }
                erase_with_iterator(iterator - 1);
                return;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        void erase_after(ElementPtr_Weak element) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&a = shared_element](auto const& elem) {
                              return a.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element before in the elements vector");
                }
                if (iterator == m_elements.end() - 1) {
                    throw BadElementErase("No element after the provided element");
                }
                erase_with_iterator(iterator + 1);
                return;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        void erase_this(ElementPtr_Weak to_delete) {
            if (auto const shared_to_delete = to_delete.lock(); shared_to_delete) {
                auto const iterator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&d = shared_to_delete](auto const elem) {
                              return d.get() == elem.get();
                          });
                if (iterator == m_elements.end()) {
                    throw BadElementPointer("not able to find element in the elements vector");
                }
                erase_with_iterator(iterator);
                return;
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        virtual void resize() {};
    };
} // namespace uil
