#include <hadoop/Pipes.hh>

#include <boost/python.hpp>
using namespace boost::python;

#include "pipes_test_support.hpp"

#include <string>
#include <iostream>

tuple get_record_from_record_reader(RecordReader* rr){
  std::string k;
  std::string v;
  bool f = rr->next(k, v);
#if 0
  std::cerr << "get_record_from_record_reader: ("<< f 
	    <<", " << k
	    <<", " << v << ")" << std::endl;
#endif
  str key(k);
  str value(v);
  return make_tuple(f, key, value);
}

float get_progress_from_record_reader(RecordReader* rr){
  float p = rr->getProgress();
  return p;
}

//+++++++++++++++++++++++++++++++++++++++++
// Exporting class definitions.
//+++++++++++++++++++++++++++++++++++++++++
void export_pipes_test_support() 
{
  class_<test_factory>("TestFactory",
		       init<Factory&>())
    .def("createRecordReader", &test_factory::createRecordReader,
	 return_value_policy<manage_new_object>())
    .def("createMapper", &test_factory::createMapper,
	 return_value_policy<manage_new_object>())
    .def("createReducer",&test_factory::createReducer,
	 return_value_policy<manage_new_object>())
    ;
  def("wrap_JobConf_object", wrap_JobConf_object,
      return_internal_reference<>());
  def("get_JobConf_object", get_JobConf_object,
      return_value_policy<manage_new_object>());
  def("get_TaskContext_object", get_TaskContext_object,
      return_value_policy<manage_new_object>());
  def("get_MapContext_object", get_MapContext_object,
      return_value_policy<manage_new_object>());
  def("get_ReduceContext_object", get_ReduceContext_object,
      return_value_policy<manage_new_object>());
  def ("double_a_string", double_a_string);
  //
  def("get_record_from_record_reader", get_record_from_record_reader);
  def("get_progress_from_record_reader", get_progress_from_record_reader);
}

