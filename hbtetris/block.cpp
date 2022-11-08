#include "block.h"
#include <stdlib.h>

// 块id由主id和子id组合而成
#define BLK_ID(major, sub) (major | (sub << 16))
// 主id占低16位
#define BLK_MAJOR_ID(id) (id & 0x0000ffff)
// 子id占高16位
#define BLK_SUB_ID(id) ((id & 0xffff0000) >> 16)

// clang-format off
// 长条
block_t I0 = {
  .id= BLK_ID('I', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
  }
};

block_t I1 = {
  .id= BLK_ID('I', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
  }
};

// L 型
block_t L0 = {
  .id= BLK_ID('L', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
  }
};

block_t L1 = {
  .id= BLK_ID('L', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,  
    0, 0, 1, 0,  
    1, 1, 1, 0,  
    0, 0, 0, 0,  
  }
};

block_t L2 = {
  .id= BLK_ID('L', 2), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
  }
};

block_t L3 = {
  .id= BLK_ID('L', 3), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
  }
};

// J型
block_t J0 = {
  .id= BLK_ID('J', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 1, 1, 0,
  }
};

block_t J1 = {
  .id= BLK_ID('J', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
  }
};

block_t J2 = {
  .id= BLK_ID('J', 2), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
  }
};

block_t J3 = {
  .id= BLK_ID('J', 3), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 1, 0,
  }
};


// 方块
block_t O0 = {
  .id= BLK_ID('O', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
  }
};

// S 型
block_t S0 = {
  .id= BLK_ID('S', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
  }
};

block_t S1 = {
  .id= BLK_ID('S', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
  }
};


// T  4种状态
block_t T0 = {
  .id= BLK_ID('T', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
  }
};

block_t T1 = {
  .id= BLK_ID('T', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
  }
};

block_t T2 = {
  .id= BLK_ID('T', 2), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
  }
};

block_t T3 = {
  .id= BLK_ID('T', 3), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
  }
};


// z型 两种状态
block_t Z0 = {
  .id= BLK_ID('Z', 0), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
  } 
};

block_t Z1 = {
  .id= BLK_ID('Z', 1), 
  .cols = 4,
  .rows = 4,
  .shape = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
  }
};


block_t* blocks[] = {
  &I0, &I1, 
  &J0, &J1, &J2, &J3,
  &L0, &L1, &L2, &L3,
  &O0,
  &S0, &S1,
  &T0, &T1, &T2, &T3,
  &Z0, &Z1,
};

block_group_t I = {'I', 2, {&I0, &I1}};
block_group_t J = {'J', 4, {&J0, &J1, &J2, &J3}};
block_group_t L = {'L', 4, {&L0, &L1, &L2, &L3}};
block_group_t O = {'O', 1, {&O0}};
block_group_t S = {'S', 2, {&S0, &S1}};
block_group_t T = {'T', 4, {&T0, &T1, &T2, &T3}};
block_group_t Z = {'Z', 2, {&Z0, &Z1}};


// 方便从id直接随机访问，如groups[id - 'A']
// 索引 0 ~ A, 1 ~ B
block_group_t* groups[] = {
// A,  B,  C,  D,  E,  F,  G,  H,  I,  J,
   0,  0,  0,  0,  0,  0,  0,  0, &I, &J,
// K,  L,  M,  N,  O,  P,  Q,  R,  S,  T,
   0, &L,  0,  0, &O,  0,  0,  0, &S, &T,
// U,  V,  W,  X,  Y,  Z
   0,  0,  0,  0,  0, &Z
};

// clang-format on

block_t* block_random() {
  // 随机选择id
  // int id_count = sizeof(block_ids) / sizeof(int);
  // int indx = rand() % id_count;
  // int id = block_ids[indx];

  int block_count = sizeof(blocks) / sizeof(block_t*);
  int indx = rand() % block_count;
  block_t* ablock = blocks[indx];

  return ablock;
}

// 获取方块所在分组
block_group_t* block_get_group(block_t* block) {
  int major_id = BLK_MAJOR_ID(block->id);
  if (major_id < 'A' || major_id > 'Z')
    return nullptr;
  int group_idx = major_id - 'A';
  return groups[group_idx];
}

// 找出旋转后的子图形
block_t* block_get_rotate_shape(block_t* block) {
  if (!block)
    return nullptr;

  block_group_t* group = block_get_group(block);
  if (!group)
    return nullptr;

  // 旋转就是在分组列表中找到子序号加1之后的块
  int block_subid = BLK_SUB_ID(block->id);
  int a_subid = (block_subid + 1) % group->subs;

  block_t* ablock = group->blocks[a_subid];
  return ablock;
}

// 获取格子的值
int block_get_cell(block_t* block, int x, int y) {
  int idx = y * block->cols + x;
  return block->shape[idx];
}

// 判断是否一个有效格子满足条件. 类似javascript中的数组的函数式方法
// dx, dy 方便给回调函数一个修正参数，在某些时候可以节省一些额外的函数定义
bool block_some_cell(block_t* block,
                     int dx,
                     int dy,
                     bool (*predicate)(int, int)) {
  int* shape = block->shape;

  for (int y = 0; y < block->rows; y++) {
    for (int x = 0; x < block->cols; x++) {
      int idx = y * block->cols + x;
      int cell = shape[idx];
      // 非有效格子
      if (!cell)
        continue;

      if (predicate(x + dx, y + dy)) {
        return true;
      }
    }
  }
  return false;
}

// 判断是否一个有效格子满足条件.
void block_foreach_cell(block_t* block,
                        int dx,
                        int dy,
                        void (*predicate)(int, int)) {
  int* shape = block->shape;

  for (int y = 0; y < block->rows; y++) {
    for (int x = 0; x < block->cols; x++) {
      int idx = y * block->cols + x;
      int cell = shape[idx];
      if (!cell)
        continue;

      predicate(x + dx, y + dy);
    }
  }
}