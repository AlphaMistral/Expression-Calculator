//
//  Macros.h
//  CPPTest
//
//  Created by 于京平 on 16/8/6.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Macros_h
#define Macros_h

#define DELETE_ARRAY(x, z) \
for (int i = 0;i < x;i++)     \
delete[] z[i];                \
delete[]z;

#define CREATE_ARRAY(x, y, type, name) \
type **name = new type*[x];\
for (int i = 0;i < x;i++)\
name[i] = new type[y];\

#endif /* Macros_h */
