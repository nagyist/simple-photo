/*****************************************************************
Copyright 2009 Rui Barbosa Martins 

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at 

http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an 
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
either express or implied. See the License for the specific
language governing permissions and limitations under the License.
*****************************************************************/

/*
 * LruCacheTests.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/LruCache.h"

using simplephoto::LruCache;

TEST(LruCacheTests, TestGettingNonExistentValue) {
  LruCache<int, int> cache(42);
  CHECK_EQUAL(NULL, cache.Get(42));
}

TEST(LruCacheTests, TestCachedValue) {
  LruCache<int, int> cache(42);
  cache.Put(42, new int(21));
  CHECK_EQUAL(21, *(cache.Get(42)));
}

TEST(LruCacheTests, TestEvictingOneValue) {
  LruCache<int, int> cache(1);
  cache.Put(42, new int(42));
  cache.Put(21, new int(21));
  CHECK_EQUAL(NULL, cache.Get(42));
  CHECK_EQUAL(21, *(cache.Get(21)));
}

TEST(LruCacheTests, TestEvictingMultipleValues) {
  LruCache<int, int> cache(1);
  for (int i = 0; i < 42; ++i) {
    CHECK_EQUAL(NULL, cache.Get(i));
    cache.Put(i, new int(i));
    CHECK_EQUAL(i, *(cache.Get(i)));
  }
}

TEST(LruCacheTests, TestEvictingAndPuttingAgain) {
  LruCache<int, int> cache(1);
  cache.Put(42, new int(42));
  cache.Put(21, new int(21));
  cache.Put(42, new int(42));
  CHECK_EQUAL(NULL, cache.Get(21));
  CHECK_EQUAL(42, *(cache.Get(42)));
}
