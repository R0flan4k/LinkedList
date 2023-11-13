#include <stdio.h>

#include "list.h"
#include "my_assert.h"

int main(void)
{
    LinkedList lst = {};

    Error_t errors = 0;

    if (errors = list_ctor(&lst))
    {
        return errors;
    }

    if (errors = list_insert(&lst, 0, 13))
    {
        return errors;
    }

    if (errors = list_insert(&lst, 1, 133))
    {
        return errors;
    }

    if (errors = list_insert(&lst, 2, 1333))
    {
        return errors;
    }

    if (errors = list_delete(&lst, 3))
    {
        return errors;
    }

    list_dump(&lst);
    system("dot ./graphviz/list_dump.dot -T png -o ./graphviz/list_dump.png");

    if (errors = list_dtor(&lst))
    {
        return errors;
    }

    return 0;
}
