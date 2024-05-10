#include <iostream>

#include "application.h"
#include "support.h"

cl_application::cl_application(cl_base* ptr = nullptr, const std::string& name = "root")
    : cl_base(ptr, name) {}


void cl_application::build_tree_objects() {
  std::string root;
  std::cin >> root;
  this->Rename(root);

  std::string input_head_path;
  std::string sub;
  int class_number;
  cl_base* last = this;
  while (true) {
    std::cin >> input_head_path;
    if (input_head_path == "endtree") {
      break;
    }
    std::cin >> sub >> class_number;
    cl_base* head_obj = last->GetObjectByPath(input_head_path);
    if (head_obj->GetSub(sub) == nullptr && head_obj != nullptr) {
      switch (class_number) {
        case 2:
          last = new cl2(head_obj, sub);
          break;
        case 3:
          last = new cl3(head_obj, sub);
          break;
        case 4:
          last = new cl4(head_obj, sub);
          break;
        case 5:
          last = new cl5(head_obj, sub);
          break;
        case 6:
          last = new cl6(head_obj, sub);
          break;
      }
    }
  }
}

int cl_application::exec_app() {
  std::cout << "Object tree\n";
  this->PrintTreeFromThis();
  std::string command;
  std::string operator_path;
  cl_base* current_object = this;
  while (1) {
    std::cin >> command;
    if (command == "END") {
      std::cout << "Current object hierarchy tree\n";
      this->PrintTreeFromThis();
      return 0;
    }
    std::cin >> operator_path;
    if (command == "SET") {
      auto tmp_object = current_object->GetObjectByPath(operator_path);
      if (tmp_object == nullptr) {
        std::cout << "The object was not found at the specified coordinate: " << operator_path << "\n";
      }
      else {
        current_object = tmp_object;
        std::cout << "Object is set: " << current_object->GetName() << "\n";
      }
    }

    else if (command == "FIND") {
      std::cout << operator_path;
      auto tmp_object = current_object->GetObjectByPath(operator_path);
      if (tmp_object == nullptr) {
        std::cout << "     Object is not found\n";
      }
      else {
        std::cout << "     Object name: " << tmp_object->GetName() << "\n";
      }
    }

    else if (command == "MOVE") {
      auto tmp_object = current_object->GetObjectByPath(operator_path);
      if (tmp_object == nullptr) {
        std::cout << operator_path << "     Head object is not found\n";
      }
      else {
        bool success = current_object->ChangeHead(tmp_object);
        if (success) {
          std::cout << "New head object: " << tmp_object->GetName() << "\n";
        }
        else if (tmp_object->GetSub(current_object->GetName()) != nullptr) {
          std::cout << operator_path << "     Dubbing the names of subordinate objects\n";
        }
        else {
          std::cout << operator_path << "     Redefining the head object failed\n";
        }
      }
    }

    else if (command == "DELETE") {
      auto tmp_object = current_object->GetSub(operator_path);
      if (tmp_object != nullptr) {
        std::string absolute_path = "/" + tmp_object->GetName();
        auto tmp_head_object = tmp_object->GetHead();

        if (current_object->DeleteByName(tmp_object->GetName())) {
          while (tmp_head_object->GetHead() != nullptr) {
            absolute_path = "/" + tmp_head_object->GetName() + absolute_path;
            tmp_head_object = tmp_head_object->GetHead();
          }
          std::cout << "The object " << absolute_path << " has been deleted\n";
        }
      }
    }
  }
}
