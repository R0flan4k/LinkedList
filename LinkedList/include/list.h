#ifndef LIST_H
    #define LIST_H

    #include <stdio.h>

    typedef int Elem_t;
    typedef int Error_t;

    #define list_dump(lst) list_dump_internal((lst), #lst, __func__, __LINE__, __FILE__)
    #define ELEM_SPEC "%d"

    enum ListResizeModes {
        LIST_RESIZE_EXPAND,
        LIST_RESIZE_CONSTRICT,
    };

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
        LIST_ERROR_CANT_INSERT_TO_FREE  = 1 << 11,
        LIST_ERROR_CANT_DELETE_FREE     = 1 << 12,
    };

    struct LinkedList {
        Elem_t * data;
        size_t * next;
        int * prev;
        size_t capacity;
        size_t head;
        size_t tail;
        int free;
    };

    Error_t list_ctor(LinkedList * lst);
    Error_t list_dtor(LinkedList * lst);
    Error_t list_vtor(LinkedList * lst);
    void list_dump_internal(LinkedList * lst,
                            const char * lst_name, const char * func,
                            const int line, const char * file);
    Error_t list_insert(LinkedList * lst, size_t elem_id, Elem_t val);
    Error_t list_push_front(LinkedList * lst, Elem_t val);
    #if 0
        delete front, delete back, push back
    #endif
    Error_t list_delete(LinkedList * lst, size_t elem_id);
    Error_t list_resize(LinkedList * lst, ListResizeModes mode, size_t resize_coefficient);
    Error_t get_elem_actual_index_by_serial_index(LinkedList * lst,
                                                  size_t serial_id, ///
                                                  int * actual_id);

    extern const char * LIST_DUMP_FILE_NAME;

#endif // LIST_H
