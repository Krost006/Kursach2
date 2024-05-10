#pragma once

#include <string>

#include "base.h"

class cl_application :public cl_base {
 public:
  explicit cl_application(cl_base* ptr, std::string&& name);

  void build_tree_objects();

  int exec_app();
};