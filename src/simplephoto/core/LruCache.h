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
 * LruCache.h
 *
 *  Created on: Oct 11, 2009
 *      Author: ruibm
 */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <map>

#include "simplephoto/core/Macros.h"

namespace simplephoto {

template <typename K, typename V>
class LruNode {
public:
  LruNode(const K& key, V* value)
      : m_key(key),
        m_value(value),
        m_previous(NULL),
        m_next(NULL) {
  }

  const K m_key;
  boost::scoped_ptr<V> const m_value;
  LruNode* m_previous;
  LruNode* m_next;
};

template <typename K, typename V>
class LruCache {
public:
  explicit LruCache(int max_nodes);
  ~LruCache();

  V* Get(const K& key);
  void Put(const K& key, V* value);

private:
  std::map<K, LruNode<K, V>* > m_nodes;
  LruNode<K, V>* m_head;
  LruNode<K, V>* m_tail;
  int m_max_nodes;
  int m_node_count;

  DISABLE_MAGIC_METHODS(LruCache);
};


/***************************************************
  Implementation
****************************************************/

template <typename K, typename V>
LruCache<K, V>::LruCache(int max_nodes)
    : m_head(NULL),
      m_tail(NULL),
      m_max_nodes(max_nodes),
      m_node_count(0) {
  assert(max_nodes > 0);
}

template <typename K, typename V>
LruCache<K, V>::~LruCache() {
  while(m_head != NULL) {
    LruNode<K, V>* node = m_head;
    m_head = node->m_next;
    delete node;    
  }
  m_head = NULL;
  m_tail = NULL;
  m_nodes.clear();
  m_node_count = 0;
}

template <typename K, typename V>
V* LruCache<K, V>::Get(const K& key) {
  if (m_nodes.find(key) == m_nodes.end()) {
    return NULL;
  } else {
    return m_nodes[key]->m_value.get();
  }
}

template <typename K, typename V>
void LruCache<K, V>::Put(const K& key, V* value) {  
  // If the node exists move it to the top of the list.
  if (m_nodes.find(key) != m_nodes.end()) {
    LruNode<K, V>* node = m_nodes[key];
    if (node->m_next != NULL) {
      node->m_next->m_previous = node->m_previous;
      node->m_next = NULL;
    } else {
      m_tail = node->m_previous;
    }
    if (node->m_previous != NULL) {
      node->m_previous->m_next = node->m_next;
      node->m_previous = NULL;
    }
    if (m_head != NULL) {
      m_head->m_previous = node;
      node->m_next = m_head;
    }
    return;
  }

  // If the node doesn't exist.
  LruNode<K, V>* node = new LruNode<K, V>(key, value);
  if (m_head != NULL) {
    node->m_next = m_head;
    m_head->m_previous = node;
  } else {
    m_tail = node;
  }
  m_head = node;
  m_nodes[key] = node;
  ++m_node_count;

  if (m_node_count > m_max_nodes) {
    node = m_tail;
    m_tail = m_tail->m_previous;
    m_tail->m_next = NULL;
    m_nodes.erase(node->m_key);
    delete node;
    --m_node_count;
  }
}

}  // namespace simplephoto

#endif // LRUCACHE_H
