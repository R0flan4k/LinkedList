#ifndef LIST_H
    #define LIST_H

    typedef int Elem_t;
    typedef int Error_t;

    enum ListErrorsMasks {
        LIST_ERROR_CANT_ALLOCATE_MEMORY = 1 << 0,
        LIST_ERROR_INVALID_ELEM_ID      = 1 << 1,
        LIST_ERROR_ALREADY_CONSTRUCTED  = 1 << 2,
        LIST_ERROR_ALREADY_DESTRUCTED   = 1 << 3,
        LIST_ERROR_INVALID_CAPACITY     = 1 << 4,
        LIST_ERROR_INVALID_HEAD         = 1 << 5,
        LIST_ERROR_INVALID_TAIL         = 1 << 6,
        LIST_ERROR_INVALID_FREE         = 1 << 7,
        LIST_ERROR_INVALID_DATA         = 1 << 8,
        LIST_ERROR_INVALID_NEXT         = 1 << 9,
        LIST_ERROR_INVALID_PREV         = 1 << 10,
    };

    struct LinkedList {
        Elem_t * data;
        size_t * next;
        size_t * prev;
        size_t capacity;
        size_t head;
        size_t tail;
        size_t free;
    };

    Error_t list_ctor(LinkedList * lst);
    Error_t list_dtor(LinkedList * lst);
    Error_t list_vtor(LinkedList * lst);
    void list_dump_internal(LinkedList * lst, Error_t errors,
                            char * lst_name, const char * func,
                            const int line, const char * file);
    Error_t list_insert(LinkedList * lst, size_t elem_id, Elem_t val);
    Error_t list_delete(LinkedList * lst, size_t elem_id);
    Error_t try_to_find_in_this_linked_list_this_given_value_using_keyboard_mouse_your_hands_brain_and_eyes_also_fingers_may_be(LinkedList * lst,
                                                                                                                                Elem_t val,
                                                                                                                                size_t * val_id);

#endif // LIST_H
