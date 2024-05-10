#include "application.h"

int main() {
	cl_application ob_cl_application(nullptr, "root");
	ob_cl_application.build_tree_objects();
  return ob_cl_application.exec_app();
}
