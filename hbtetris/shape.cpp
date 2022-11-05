#include "shape.h"
#include <stdlib.h>

// clang-format off

// ����
int I0[] = {
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
};

int I1[] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 1, 1, 1,
  0, 0, 0, 0,
};

// L ��
int L0[] = {
  0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 0,
};

int L1[] = {
  0, 0, 0, 0,  
  0, 0, 1, 0,  
  1, 1, 1, 0,  
  0, 0, 0, 0,  
};

int L2[] = {
  0, 0, 0, 0,
  1, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
};

int L3[] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 1, 1, 0,
  1, 0, 0, 0,
};


// J��
int J0[] = {
  0, 0, 0, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 1, 1, 0,
};

int J1[] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 1, 1, 0,
  0, 0, 1, 0,
};

int J2[] = {
  0, 0, 0, 0,
  1, 1, 0, 0,
  1, 0, 0, 0,
  1, 0, 0, 0,
};

int J3[] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 0, 0, 0,
  1, 1, 1, 0,
};


// ����
int O0[] = {
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
};

// S ��
int S0[] = {
  0, 0, 0, 0,
  0, 1, 1, 0,
  1, 1, 0, 0,
  0, 0, 0, 0,
};

int S1[] = {
  0, 0, 0, 0,
  1, 0, 0, 0,
  1, 1, 0, 0,
  0, 1, 0, 0,
};


// T  4��״̬
int T0[] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 1, 1, 0,
  0, 1, 0, 0,
};

int T1[] = {
  0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 0,
  0, 1, 0, 0,
};

int T2[] = {
  0, 0, 0, 0,
  0, 1, 0, 0,
  1, 1, 1, 0,
  0, 0, 0, 0,
};

int T3[] = {
  0, 0, 0, 0,
  0, 1, 0, 0,
  1, 1, 0, 0,
  0, 1, 0, 0,
};


// z�� ����״̬
int Z0[] = {
  0, 0, 0, 0,
  1, 1, 0, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
};

int Z1[] = {
  0, 0, 0, 0,
  0, 1, 0, 0,
  1, 1, 0, 0,
  1, 0, 0, 0,
};

// clang-format on

//
block_t I = {'I', 2, {I0, I1}};

block_t J = {'J', 4, {J0, J1, J2, J3}};

block_t L = {'L', 4, {L0, L1, L2, L3}};

block_t O = {'O', 1, {O0}};

block_t S = {'S', 2, {S0, S1}};

block_t T = {'T', 4, {T0, T1, T2, T3}};

block_t Z = {'Z', 2, {Z0, Z1}};

// ��֯�������У��Ա�������
block_t* blocks[] = {&I, &J, &L, &O, &S, &T, &Z};

block_t* block_random() {
  int indx = rand() % 7;
  return blocks[indx];
}

// ���Ҳ��Կ������Ż��ռ�
int* block_get_shape(int id, int subid) {
  for (int i = 0; i < 7; i++) {
    if (blocks[i]->id == id) {
      if (subid >= 0 && subid < blocks[i]->subs) {
        return blocks[i]->shapes[subid];
      }
    }
  }
  return 0;
}

// �ҳ���ת�����ͼ��
int block_get_rotate_shape(int id, int subid) {
  for (int i = 0; i < 7; i++) {
    if (blocks[i]->id == id) {
      int new_subid = (subid + 1) % blocks[i]->subs;
      return new_subid;
    }
  }
  return 0;
}

block_t* block_get(int id) {
  for (int i = 0; i < 7; i++) {
    if (blocks[i]->id == id) {
      return blocks[i];
    }
  }
  return 0;
}

/**
 * �ж��Ƿ�һ����Ч������������.
 *
 * \param predicate �жϻص�
 * \return
 */
bool block_some_cell(int id, int subid, bool (*predicate)(int, int)) {
  int* shape = block_get_shape(id, subid);

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int idx = y * 4 + x;
      int cell = shape[idx];
      // ����Ч����
      if (!cell)
        continue;

      if (predicate(x, y)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * �ж��Ƿ�һ����Ч������������.
 *
 * \param predicate �жϻص�
 * \return
 */
void block_foreach_cell(int id, int subid, void (*predicate)(int, int)) {
  int* shape = block_get_shape(id, subid);

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int idx = y * 4 + x;
      int cell = shape[idx];
      if (!cell)
        continue;

      predicate(x, y);
    }
  }
}