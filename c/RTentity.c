/* automatically created by mc from /home/gaius/GM2/graft-5.4.0/gcc-5.4.0/gcc/gm2/gm2-libs-iso/RTentity.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#define _RTentity_H
#define _RTentity_C

#   include "Glibc.h"
#   include "GM2RTS.h"

typedef struct _T1_r _T1;

typedef _T1 *RTentity_Group;

struct _T1_r {
               RTentity_Group left;
               RTentity_Group right;
               void *entity;
               unsigned int entityKey;
             };

RTentity_Group RTentity_InitGroup (void);
RTentity_Group RTentity_KillGroup (RTentity_Group g);
unsigned int RTentity_GetKey (RTentity_Group g, void * a);
void RTentity_PutKey (RTentity_Group g, void * a, unsigned int key);

/*
   DelKey - deletes an entry in the binary tree.

            NB in order for this to work we must
            ensure that the InitGroup sets
            both left and right to NIL.
*/

void RTentity_DelKey (RTentity_Group g, void * a);
unsigned int RTentity_IsIn (RTentity_Group g, void * a);

/*
   findChildAndParent - find a node, child, in a binary tree, t, with name
                        equal to n.  If an entry is found, parent is set
                        to the node above child.
*/

static void findChildAndParent (RTentity_Group t, void * a, RTentity_Group *child, RTentity_Group *parent);


/*
   findChildAndParent - find a node, child, in a binary tree, t, with name
                        equal to n.  If an entry is found, parent is set
                        to the node above child.
*/

static void findChildAndParent (RTentity_Group t, void * a, RTentity_Group *child, RTentity_Group *parent)
{
  (*parent) = t;
  if (t == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-5.4.0/gcc-5.4.0/gcc/gm2/gm2-libs-iso/RTentity.mod", 71, 207, (char *) "findChildAndParent", 18, (char *) "internal runtime error, RTentity is either corrupt or the module storage has not been initialized yet", 101);
  (*child) = t->left;
  if ((*child) != NULL)
    do {
      if (a < (*child)->entity)
        {
          (*parent) = (*child);
          (*child) = (*child)->left;
        }
      else if (a > (*child)->entity)
        {
          (*parent) = (*child);
          (*child) = (*child)->right;
        }
    } while (! (((*child) == NULL) || (a == (*child)->entity)));
}

RTentity_Group RTentity_InitGroup (void)
{
  RTentity_Group g;

  g = libc_malloc ((unsigned int) sizeof ((*g)));
  g->left = NULL;
  g->right = NULL;
  g->entity = NULL;
  g->entityKey = 0;
  return g;
}

RTentity_Group RTentity_KillGroup (RTentity_Group g)
{
  if (g != NULL)
    {
      g->left = RTentity_KillGroup (g->left);
      g->right = RTentity_KillGroup (g->right);
      libc_free ((void *) g);
    }
  return NULL;
}

unsigned int RTentity_GetKey (RTentity_Group g, void * a)
{
  RTentity_Group parent;
  RTentity_Group child;

  findChildAndParent (g, a, &child, &parent);
  if (child == NULL)
    return 0;
  else
    return child->entityKey;
}

void RTentity_PutKey (RTentity_Group g, void * a, unsigned int key)
{
  RTentity_Group parent;
  RTentity_Group child;

  findChildAndParent (g, a, &child, &parent);
  if (child == NULL)
    {
      if (parent == g)
        {
          child = libc_malloc ((unsigned int) sizeof ((*child)));
          parent->left = child;
        }
      else
        if (a < parent->entity)
          {
            child = libc_malloc ((unsigned int) sizeof ((*child)));
            parent->left = child;
          }
        else if (a > parent->entity)
          {
            child = libc_malloc ((unsigned int) sizeof ((*child)));
            parent->right = child;
          }
      child->right = NULL;
      child->left = NULL;
      child->entity = a;
      child->entityKey = key;
    }
  else
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-5.4.0/gcc-5.4.0/gcc/gm2/gm2-libs-iso/RTentity.mod", 71, 110, (char *) "PutKey", 6, (char *) "internal runtime error, entity already stored", 45);
}


/*
   DelKey - deletes an entry in the binary tree.

            NB in order for this to work we must
            ensure that the InitGroup sets
            both left and right to NIL.
*/

void RTentity_DelKey (RTentity_Group g, void * a)
{
  RTentity_Group i;
  RTentity_Group child;
  RTentity_Group parent;

  findChildAndParent (g, a, &child, &parent);
  if ((child != NULL) && (child->entity == a))
    if (parent->right == child)
      {
        if (child->left != NULL)
          {
            i = child->left;
            while (i->right != NULL)
              i = i->right;
            i->right = child->right;
            parent->right = child->left;
          }
        else
          parent->right = child->right;
        libc_free ((void *) child);
      }
    else
      {
        if (child->right != NULL)
          {
            i = child->right;
            while (i->left != NULL)
              i = i->left;
            i->left = child->left;
            parent->left = child->right;
          }
        else
          parent->left = child->left;
        libc_free ((void *) child);
      }
  else
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-5.4.0/gcc-5.4.0/gcc/gm2/gm2-libs-iso/RTentity.mod", 71, 188, (char *) "DelKey", 6, (char *) "internal runtime error, trying to delete an entity which is not in the tree", 75);
}

unsigned int RTentity_IsIn (RTentity_Group g, void * a)
{
  RTentity_Group child;
  RTentity_Group parent;

  findChildAndParent (g, a, &child, &parent);
  return child != NULL;
}

void _M2_RTentity_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_RTentity_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
