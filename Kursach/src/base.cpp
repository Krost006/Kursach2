#include <iostream>
#include <queue>
#include <utility>

#include "base.h"

cl_base::cl_base(cl_base* root, cl_base* head, std::string&& name)
    : root(root), head(head), name(std::move(name)) {
  if (head != nullptr) {
    head->subordinate.push_back(this);
  }
  status = 0;
}

cl_base::~cl_base() {
  for (auto& child : subordinate) {
    delete child;
  }
}

bool cl_base::Rename(const std::string& new_name) {
  if (head == nullptr || head->GetSub(new_name) == nullptr) {
    name = new_name;
    return true;
  }
  return false;
}

std::string cl_base::GetName() {
  return name;
};

cl_base* cl_base::GetHead() {
  return head;
};

cl_base* cl_base::GetRoot() {
  return root;
}

cl_base* cl_base::GetSub(const std::string& child_file) {
  for (auto child : subordinate) {
    if (child->GetName() == child_file) {
      return child;
    }
  }
  return nullptr;
}

cl_base* cl_base::GetSubOnBranch(const std::string& successor) {
  std::queue < cl_base * > queue;
  queue.push(this);
  int counter = 0;
  cl_base* answer = nullptr;
  while (!queue.empty()) {
    cl_base* current = queue.front();
    queue.pop();
    for (auto child : current->subordinate) {
      if (child->GetName() == successor) {
        ++counter;
        answer = child;
      }
      queue.push(child);
    }
  }

  if (counter != 1) {
    return nullptr;
  }
  return answer;
}

cl_base* cl_base::GetSubOnTree(const std::string& successor) {
  if (head != nullptr) {
    return head->GetSubOnTree(successor);
  }
  return GetSubOnBranch(successor);
}

void cl_base::PrintTreeFromThis() {
  cl_base* root = head;
  int level = 0;
  while (root != nullptr) {
    level++;
    root = root->head;
  }
  std::string tab = "    ";
  for (int i = 0; i < level; ++i) {
    std::cout << tab;
  }
  std::cout << name << "\n";
  for (auto child : subordinate) {
    child->PrintTreeFromThis();
  }
}

void cl_base::PrintTreeFromThisWithStatus() {
  cl_base* root = head;
  int level = 0;
  while (root != nullptr) {
    ++level;
    root = root->head;
  }
  std::string tab = "    ";
  std::string separator = " ";
  for (int i = 0; i < level; ++i) {
    std::cout << tab;
  }
  std::cout << name << separator;
  std::cout << (status ? "is ready\n" : "is not ready\n");

  for (auto child : subordinate) {
    child->PrintTreeFromThisWithStatus();
  }
}

void cl_base::SetStatus(int new_status) {
  if (status != 0 && new_status != 0) {
    cl_base* tmp_head = head;
    bool can_change = true;

    while (tmp_head != nullptr) {
      if (tmp_head->status == 0) {
        can_change = false;
        break;
      }
      tmp_head = tmp_head->head;
    }

    if (can_change) {
      status = new_status;
    }
    return;
  }

  if (status != 0) {
    status = 0;
    for (auto child : subordinate) {
      child->SetStatus(new_status);
    }
  }
}

bool cl_base::ChangeHead(cl_base* new_head) {
  if (head == nullptr || new_head == nullptr) {
    return false;
  }

  if (new_head->GetSub(name) != nullptr) {
    return false;
  }

  cl_base* ptr = new_head;
  while (ptr != this && ptr != nullptr) {
    ptr = ptr->head;
  }
  if (ptr == this) {
    return false;
  }

  for (int i = 0; i < head->subordinate.size(); ++i) {
    if (head->subordinate[i] == this) {
      head->subordinate.erase(head->subordinate.begin() + i);
      break;
    }
  }

  head = new_head;
  new_head->subordinate.push_back(this);
  return true;
}

bool cl_base::DeleteByName(const std::string& direct_child) {
  cl_base* object = GetSub(direct_child);
  if (object == nullptr) {
    return false;
  }

  for (int i = 0; i < subordinate.size(); ++i) {
    if (subordinate[i] == object) {
      delete object;
      subordinate.erase(subordinate.begin() + i);
      return true;
    }
  }
  return false;
}

cl_base* cl_base::GetObjectByPath(std::string path) {
  char separator = '.';

  if (path[0] == '/') {
    if (head != nullptr) {
      return head->GetObjectByPath(path);
    }
    separator = '/';
    path = path.substr(1);
  }

  if (path == "" || path == ".") {
    return this;
  }

  if (path[0] == separator) {
    return GetSubOnBranch(path.substr(1));
  }

  int index = path.find('/');
  if (index == std::string::npos) {
    return GetSub(path);
  }

  std::string object_name = path.substr(0, index);
  if (GetSub(object_name) == nullptr) {
    return nullptr;
  }

  return GetSub(object_name)->GetObjectByPath(path.substr(index + 1));
}
