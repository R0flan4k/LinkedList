#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "my_assert.h"

const size_t START_CAPACITY = 16;
const size_t DUMMY_NODE_ID = 0;
const long TRASH_VALUE = 0x5051AB1BA5;
void * TRASH_POINTER = nullptr;

Error_t set_list_head(LinkedList * lst, size_t new_head_id);
Error_t set_list_tail(LinkedList * lst, size_t new_tail_id);
Error_t list_reference_arrays_vtor(LinkedList * lst);


Error_t list_ctor(LinkedList * lst)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (!list_vtor(lst))
    {
        errors |= LIST_ERROR_ALREADY_CONSTRUCTED;
        return errors;
    }

    if (!(lst->data = (Elem_t *) calloc(START_CAPACITY, sizeof(Elem_t))) ||
        !(lst->next = (size_t *) calloc(START_CAPACITY, sizeof(size_t))) ||
        !(lst->prev = (size_t *) calloc(START_CAPACITY, sizeof(size_t))))
    {
        errors |= LIST_ERROR_CANT_ALLOCATE_MEMORY;
        return errors;
    }
    lst->capacity = START_CAPACITY;

    set_list_head(lst, DUMMY_NODE_ID);
    set_list_tail(lst, DUMMY_NODE_ID);

    lst->free = 1;

    for (size_t i = 1; i < START_CAPACITY; i++)
    {
        lst->next[i] = i + 1;
        lst->prev[i] = i - 1;
    }

    return errors;
}


Error_t list_dtor(LinkedList * lst)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (lst->data == TRASH_POINTER && lst->next == TRASH_POINTER &&
        lst->prev == TRASH_POINTER && lst->capacity == TRASH_VALUE &&
        lst->head == TRASH_VALUE   && lst->tail == TRASH_VALUE &&
        lst->free == TRASH_VALUE)
    {
        errors |= LIST_ERROR_ALREADY_DESTRUCTED;
        return errors;
    }

    if (errors = list_vtor(lst))
    {
        return errors;
    }

    free(lst->data);
    free(lst->next);
    free(lst->prev);

    lst->data = (Elem_t *) TRASH_POINTER;
    lst->next = (size_t *) TRASH_POINTER;
    lst->prev = (size_t *) TRASH_POINTER;

    lst->capacity = TRASH_VALUE;
    lst->head     = TRASH_VALUE;
    lst->tail     = TRASH_VALUE;
    lst->free     = TRASH_VALUE;

    return errors;
}


Error_t list_vtor(LinkedList * lst)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (lst->capacity <= 0)
        errors |= LIST_ERROR_INVALID_CAPACITY;
    if (lst->head < 0 || lst->head >= lst->capacity)
        errors |= LIST_ERROR_INVALID_HEAD;
    if (lst->tail < 0 || lst->tail >= lst->capacity)
        errors |= LIST_ERROR_INVALID_TAIL;
    if (lst->free < 0 || lst->free >= lst->capacity)
        errors |= LIST_ERROR_INVALID_FREE;

    if (!lst->data)
        errors |= LIST_ERROR_INVALID_DATA;

    Error_t reference_arrays_errors = 0;
    if (reference_arrays_errors = list_reference_arrays_vtor(lst))
        errors |= reference_arrays_errors;

    return errors;
}


void list_dump_internal(LinkedList * lst, Error_t errors,
                        char * lst_name, const char * func,
                        const int line, const char * file)
{
    MY_ASSERT(lst);
    MY_ASSERT(lst_name);
    MY_ASSERT(func);
    MY_ASSERT(file);
}


Error_t list_reference_arrays_vtor(LinkedList * lst)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (!lst->next)
    {
        errors |= LIST_ERROR_INVALID_NEXT;
        return errors;
    }

    if(!lst->prev)
    {
        errors |= LIST_ERROR_INVALID_PREV;
        return errors;
    }

    bool next_check_necessity = true;
    bool prev_check_necessity = true;
    for (size_t i = 0; i < lst->capacity; i++)
    {
        if ((lst->next[i] < 0 || lst->next[i] > lst->capacity) &&
            next_check_necessity)
        {
            errors |= LIST_ERROR_INVALID_NEXT;
        }

        if ((lst->prev[i] < 0 || lst->prev[i] > lst->capacity) &&
            prev_check_necessity)
        {
            errors |= LIST_ERROR_INVALID_PREV;
        }

        if (!next_check_necessity && !prev_check_necessity)
            break;
    }

    return errors;
}


Error_t set_list_head(LinkedList * lst, size_t new_head_id)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (new_head_id < 0 || new_head_id >= lst->capacity)
    {
        errors || LIST_ERROR_INVALID_ELEM_ID;
        return errors;
    }

    lst->next[DUMMY_NODE_ID] = new_head_id;
    lst->head                = new_head_id;

    return errors;
}


Error_t set_list_tail(LinkedList * lst, size_t new_tail_id)
{
    MY_ASSERT(lst);

    Error_t errors = 0;

    if (new_tail_id < 0 || new_tail_id >= lst->capacity)
    {
        errors || LIST_ERROR_INVALID_ELEM_ID;
        return errors;
    }

    lst->prev[DUMMY_NODE_ID] = new_tail_id;
    lst->tail                = new_tail_id;

    return errors;
}
