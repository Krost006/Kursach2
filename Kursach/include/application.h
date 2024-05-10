#pragma once

#include <string>

#include "base.h"

class cl_application :public cl_base {
 public:
  cl_application(cl_base* ptr, const std::string& name);

  void build_tree_objects();

  int exec_app();
};