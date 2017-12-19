#include <sys/types.h>
#include <limits.h>
#include <stdio.h>

#include "run.h"
#include "util.h"

void *base = 0;

p_meta find_meta(p_meta *last, size_t size)
{
    p_meta index = base;
    p_meta result = base;
    p_meta cur = sbrk(0);

    switch (fit_flag)
    {
        case FIRST_FIT:
        {
            while(index && !index->free && index->size < size)
            {
                *last = index;
                index = index->next;
            }
        }
        break;

        case BEST_FIT:
        {
            //BEST_FIT CODE
        }
        break;

        case WORST_FIT:
        {
            //WORST_FIT CODE
        }
        break;
    }
    return result;
}

void *m_malloc(size_t size)
{
    p_meta last = base;
    p_meta now = base;
    p_meta cur = sbrk(0);

    now = find_meta(&last, size);
    if (now == cur)
    {
        cur = sbrk(size);
        now->free = 0;
        now->size = size;
        now->next = cur;
        now->prev = last;
    }
    else
    {
        now->free = 0;
        now->size = size;
        now->next = now + (size + sizeof(struct metadata));
        now->prev = last;
        last->next = now;
        now->next->prev = now;
    }
    return (last + sizeof(struct metadata));   
}

void m_free(void *ptr)
{
    
}

void *m_realloc(void *ptr, size_t size)
{

}
