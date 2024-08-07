//
// Purpur Tentakel
// 06.08.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <memory>
#include <uil/context.hpp>
#include <uil/exception.hpp>
#include <vector>
#include <algorithm>

namespace uil {
    template<class T>
    class BaseManager {
    public:
        using ElementPtr      = std::shared_ptr<T>;
        using ElementPtr_Weak = std::weak_ptr<T>;
        using ElementVector   = std::vector<ElementPtr>;

    private:
        ElementVector m_elements{};
        cpt::Vec2_i m_resolution;

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_emelent_with_offset(cpt::usize const offset, Args&&... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
            return emplace_element_with_iterator<S>(m_elements.begin() + static_cast<cpt::i64>(offset),
                                                    std::forward<Args>(args)...);
        }

        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_element_with_iterator(ElementVector::iterator const& iterator, Args&&... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
            auto elem            = std::make_shared<S>(m_resolution, std::forward<Args>(args)...);
            std::weak_ptr<S> ptr = elem;
            m_elements.insert(iterator, std::move(elem));
            return ptr;
        }

        ElementPtr_Weak insert_element_with_offset(cpt::usize const offset, ElementPtr element) {
            return insert_element_with_iterator(m_elements.begin() + static_cast<cpt::i64>(offset), std::move(element));
        }

        ElementPtr_Weak insert_element_with_iterator(ElementVector::iterator const& iterator, ElementPtr element) {
            ElementPtr_Weak ptr = element;
            m_elements.insert(iterator, std::move(element));
            return ptr;
        }

        void erase_with_offset(cpt::usize const offset) {
            erase_with_iterator(m_elements.begin() + static_cast<cpt::i64>(offset));
        }

        void erase_with_iterator(ElementVector::iterator const& iterator) {
            m_elements.erase(iterator);
        }

    protected:
        [[nodiscard]] ElementVector elements() const {
            return m_elements;
        }

    public:
        /**
         *
         * @param resolution current resolution
         */
        explicit BaseManager(cpt::Vec2_i const resolution) : m_resolution{ resolution } { }

        /**
         * only for polimorphism
         */
        virtual ~BaseManager() = default;

        /**
         * constructs the element S with parameters Args... and emplaced it at the front of the element vector.
         * all empaced elements will be handled_input, updated, rendered and resized.
         *
         * S needs to be derived from T.
         * S needs to be constructable with parameters Args...
         *
         * @tparam S element that will be emplaced into the manager
         * @tparam Args all Types the element needs to be constructed
         * @param args all Parameters the element needs to be constructed
         * @return pointer of the constructed element as a weak_ptr
         */
        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_top(Args&&... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
            return emplace_emelent_with_offset<S>(0, std::forward<Args>(args)...);
        }

        /**
         * construct the element S with parameters Args... and emplaced it at the end of the element vector.
         * all empaced elements will be handle_input, updated, rendered and resized.
         *
         * S needs to be derived from T.
         * S needs to be constructable with parameters Args...
         *
         * @tparam S element that will be emplaced into the manager
         * @tparam Args all Types the element needs to be constructed
         * @param args all Parameters the element needs to be constructed
         * @return pointer of the constructed element as a weak_ptr
         */
        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_bottom(Args&&... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
            return emplace_element_with_iterator<S>(m_elements.end(), std::forward<Args>(args)...);
        }

        /**
         * construct the element S with parameters Args... and emplaced it at a certain index of the element vector.
         * all empaced elements will be handle_input, updated, rendered and resized.
         *
         * S needs to be derived from T.
         * S needs to be constructable with parameters Args...
         *
         * @tparam S element that will be emplaced into the manager
         * @tparam Args all Types the element needs to be constructed
         * @param index  provides the index the new element is empaced to
         * @param args all Parameters the element needs to be constructed
         * @return pointer of the constructed element as a weak_ptr
         * @throw BadElementIndex will throw when index is out of range
         */
        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_at(cpt::usize const index, Args&&... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
            if (index > m_elements.size()) {
                throw BadElementIndex("index is out of bounce");
            }
            if (index == m_elements.size()) {
                return emplace_bottom<S>(args...);
            }

            return emplace_emelent_with_offset<S>(index, std::forward<Args>(args)...);
        }

        /**
         * construct the element S with parameters Args... and emplaced it before a provided element of the element vector.
         * all empaced elements will be handle_input, updated, rendered and resized.
         *
         * S needs to be derived from T.
         * S needs to be constructable with parameters Args...
         *
         * @tparam S element that will be emplaced into the manager
         * @tparam Args all Types the element needs to be constructed
         * @param scene proviedes the element pointer the new element gets emplaced before
         * @param args all Parameters the element needs to be constructed
         * @return pointer of the constructed element as a weak_ptr
         * @throw BadElementPointer throws when provided scene element can not be fount in the elements vector
         * @throw BadElementPointer throws when provided scene element is expired
         */
        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_before(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
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

        /**
         * construct the element S with parameters Args... and emplaced it after a provided element of the element vector.
         * all empaced elements will be handle_input, updated, rendered and resized.
         *
         * S needs to be derived from T.
         * S needs to be constructable with parameters Args...
         *
         * @tparam S element that will be emplaced into the manager
         * @tparam Args all Types the element needs to be constructed
         * @param scene proviedes the element pointer the new element gets emplaced after
         * @param args all Parameters the element needs to be constructed
         * @return pointer of the constructed element as a weak_ptr
         * @throw BadElementPointer throws when provided scene element can not be found in the elements vector
         * @throw BadElementPointer throws when provided scene element is expired
         */
        template<std::derived_from<T> S, typename... Args>
        std::weak_ptr<S> emplace_after(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<S, cpt::Vec2_i, Args...>)
        {
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

        /**
         * pushed the element at the front of the element vector.
         * all pushed elements will be handle_input, updated, rendered and resized.
         *
         * @param to_push the element that gets pushed into the vector
         * @return pointer of the pushed element as a weak_ptr
         */
        ElementPtr_Weak push_top(ElementPtr to_push) {
            return insert_element_with_offset(0, std::move(to_push));
        }

        /**
         * pushed the element at the end of the element vector.
         * all pushed elements will be handle_input, updated, rendered and resized.
         *
         * @param to_push the element that gets pushed into the vector
         * @return pointer of the pushed element as a weak_ptr
         */
        ElementPtr_Weak push_bottom(ElementPtr to_push) {
            return insert_element_with_iterator(m_elements.end(), std::move(to_push));
        }

        /**
         * pushes the element at a certain index of the element vector.
         * all empaced elements will be handle_input, updated, rendered and resized.
         *
         * @param index provides the index the new element is pushed to
         * @param to_push the element that gets pushed into the vector
         * @return pointer of the pushed element as a weak_ptr
         * @throw BadElementIndex will throw when index is out of range
         */
        ElementPtr_Weak push_at(cpt::usize const index, ElementPtr to_push) {
            if (index > m_elements.size()) {
                throw BadElementIndex("index is out of bounce");
            }

            if (index == m_elements.size()) {
                return push_bottom(std::move(to_push));
            }

            return insert_element_with_offset(index, std::move(to_push));
        }

        /**
         * pushes the element before a provided element of the element vector.
         * all pushed elements will be handle_input, updated, rendered and resized.
         *
         * @param element proviedes a element pointer that holds the element befor the pushed element
         * @param to_push the element that gets pushed
         * @return pointer of the pushed element as a weak_ptr
         * @throw BadElementPointer throws when provided element can not be fount in the elements vector
         * @throw BadElementPointer throws when provided element is expired
         */
        ElementPtr_Weak push_before(ElementPtr_Weak element, ElementPtr to_push) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iterrator
                        = std::find_if(m_elements.begin(), m_elements.end(), [&b = shared_element](auto const& elem) {
                              return b.get() == elem.get();
                          });
                if (iterrator == m_elements.end()) {
                    throw BadElementPointer("not able to find before element in elements vector");
                }
                return insert_element_with_iterator(iterrator, std::move(to_push));
            }

            throw BadElementPointer("weak_ptr was ecpired");
        }

        /**
         * pushes the element after a provided element of the element vector.
         * all pushed elements will be handle_input, updated, rendered and resized.
         *
         * @param element proviedes a element pointer that holds the element after the pushed element
         * @param to_push the element that gets pushed
         * @return pointer of the pushed element as a weak_ptr
         * @throw BadElementPointer throws when provided element can not be fount in the elements vector
         * @throw BadElementPointer throws when provided element is expired
         */
        ElementPtr_Weak push_after(ElementPtr_Weak element, ElementPtr to_push) {
            if (auto const shared_element = element.lock(); shared_element) {
                auto const iteraor
                        = std::find_if(m_elements.begin(), m_elements.end(), [&a = shared_element](auto const& elem) {
                              return a.get() == elem.get();
                          });
                if (iteraor == m_elements.end()) {
                    throw BadElementPointer("not able to find after element in elements vector");
                }

                return insert_element_with_iterator(iteraor + 1, std::move(to_push));
            }

            throw BadElementPointer("weak_ptr was expired");
        }

        /**
         * pops the first element of the vector.
         * that is the most bottom rendered element.
         *
         * @return shared_ptr of the poped element
         * @throw BadElementErase throws when elements vector is empty
         */
        ElementPtr pop_top() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }

            auto temp = m_elements.front();
            erase_with_iterator(m_elements.begin());
            return temp;
        }

        /**
         * pops the last element of the vector.
         * that is the most front rendered element.
         *
         * @return shared_ptr of the poped element
         * @throw BadElementErase throws when elements vector is empty
         */
        ElementPtr pop_bottom() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }

            auto temp = m_elements.back();
            m_elements.pop_back();
            return temp;
        }

        /**
         * pops a specific index in the element vector.
         * notice that index 0 is the most bottom rendered element.
         *
         * @param index rovides the index that will be poped
         * @return shared_ptr of the poped element
         * @throw BadElementIndex will throw when index is out of range
         */
        ElementPtr pop_at(cpt::usize const index) {
            if (index >= m_elements.size()) {
                throw BadElementIndex("index out of range while pop at");
            }

            auto temp = m_elements.at(index);
            erase_with_offset(index);
            return temp;
        }

        /**
         * pops a element that is located one before the provided element in the elements vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param element the element before the element that will be poped
         * @return shared_ptr of the poped element
         * @throw BadElementPointer throws when provided before element can not be found in the elements vector
         * @throw BadElementPointer throws when provided before element is expired
         * @throw BadElementErase throws when provided before element is the first element in the elements vector
         */
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

        /**
         * pops a element that is located one after the provided element in the elements vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param element the element after the element that will be deleted
         * @return shared_ptr of the poped element
         * @throw BadElementPointer throws when provided after element can not be found in the elements vector
         * @throw BadElementPointer throws when provided after element is expired
         * @throw BadelementErase throws when provided after element is the last element in the elements vector
         */
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

        /**
         * pops the provided element.
         * if there are no more shared_ptr the element will get deleted.
         *
         * @param to_pop element that gets poped
         * @return shared_ptr of the poped element
         * @throw BadElementPointer throws when provided element can not be found in the elements vector
         */
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

        /**
         * erases the first element of the vector.
         * that is the most bottom rendered element.
         *
         * @throw BadElementErase thows when elements vector is empty
         */
        void erase_top() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }
            erase_with_iterator(m_elements.begin());
        }

        /**
         * erases the last element of the vector.
         * that is the most front rendered element.
         *
         * @throw BadElementErase thows when elements vector is empty
         */
        void erase_bottom() {
            if (m_elements.empty()) {
                throw BadElementErase("empty elements vector");
            }
            m_elements.pop_back();
        }

        /**
         * erases a specific index in the element vector.
         * notice that index 0 is the most bottom rendered element.
         *
         * @param index provides the index that will be erased
         * @throw BadElementIndex will throw when index is out of range
         */
        void erase_at(cpt::usize const index) {
            if (index >= m_elements.size()) {
                throw BadElementIndex("index out of range while erasing a element");
            }

            erase_with_offset(index);
        }

        /**
         * erases a element that is located one before the provided element in the elements vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param element the element before the element that will be deleted
         * @throw BadElementPointer throws when provided before element can not be found in the elements vector
         * @throw BadElementPointer throws when provided before element is expired
         * @throw BadElementErase throws when provided before element is the first element in the elements vector
         */
        void erase_before(ElementPtr_Weak element) {
            if (auto const shared_element= element.lock(); shared_element) {
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

        /**
         * erases a element that is located one after the provided element in the elements vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param element the element after the element that wiill be deleted
         * @throw BadElementPointer throws when provided after element can not be found in the elements vector
         * @throw BadElementPointer throws when provided after element is expired
         * @throw BadElementErase throws when provided after element is the last element in the elements vector
         */
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

        /**
         * erases the provided element.
         * if there are no more shared_ptr the element will get deleted.
         *
         * @param to_delete element that gets deleted
         * @throw BadElementPointer throws when provided element can not be found in the elements vector
         */
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


        /**
         * calls all emplaced element to resize.
         *
         * @param context all changes of the last frame
         */
        virtual void resize(Context const& context) {
            m_resolution = context.resolution;
        }
    };
} // namespace uil
