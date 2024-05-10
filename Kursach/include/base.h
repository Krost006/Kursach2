#pragma once

#include <string>
#include <vector>

class cl_base {
 private:
  std::string name;
  cl_base* head;
  std::vector<cl_base*> subordinate;
  int status;
 public:
  cl_base(cl_base* head, const std::string& name = "root");
  ~cl_base();

  bool Rename(const std::string& new_name);

  std::string GetName();
  cl_base* GetHead();
  cl_base* GetSub(const std::string& sub_name);

  cl_base* GetSubOnBranch(const std::string& successor);
  cl_base* GetSubOnTree(const std::string& successor);

  void PrintTreeFromThis();
  void PrintTreeFromThisWithStatus();

  void SetStatus(int new_status);

  bool ChangeHead(cl_base* new_head);
  bool DeleteByName(const std::string& direct_child);

  cl_base* GetObjectByPath(std::string path);
};