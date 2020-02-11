#include <node.h>
#include <v8.h>
#include <vector>
#include <array>
#include <iostream>
#include "bowyerwatson.h"
#include "fem.h"

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::Array;
using v8::String;
using v8::Value;
using v8::Context;
using v8::Integer;

using namespace std;

void Add(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();

  // Perform the operation
  double value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
}

void Triangular(const FunctionCallbackInfo<Value> &args)
{
  //////////////////////////////////////////////////////////////////////////////////////////
  // decode JavaScript Object to C++
  //////////////////////////////////////////////////////////////////////////////////////////
  Isolate *isolate = args.GetIsolate();
  Local<Array> arrayJS = Local<Array>::Cast(args[0]);
  int numberOfElements = args[1].As<Number>()->Value();
  // Local<Array> arrayJS = Local<Array>::Cast(objJS->Get(String::NewFromUtf8(isolate, "geometries")));

  vector<vector<double>> arrayCC(arrayJS->Length(), vector<double>(2, 0));
  for (uint32_t i=0; i<arrayJS->Length(); i++)
  {
    Local<Array> innerArrayJS = Local<Array>::Cast(arrayJS->Get(i).As<Array>());
    for (uint32_t j = 0; j <innerArrayJS->Length(); j++)
    {
      arrayCC[i][j] = innerArrayJS->Get(j).As<Number>()->Value();
    }
  }
  std::cout << "Hello \n"
            << numberOfElements << "\n"
            << arrayCC.size() << "\n";
  //////////////////////////////////////////////////////////////////////////////////////////
  // main
  //////////////////////////////////////////////////////////////////////////////////////////
  Delaunay tri;
  TwoDimensionTriangularFiniteElementMethod fem;
  vector<vector<double>> baseTriangles;
  tri.triangulate(arrayCC, numberOfElements);
  baseTriangles = tri.getTriangles();
  //////////////////////////////////////////////////////////////////////////////////////////
  // encode C++ to JavaScript
  //////////////////////////////////////////////////////////////////////////////////////////
  Local<Array> returnArrayJS = Array::New(isolate, baseTriangles.size());
  for (uint32_t i = 0; i < baseTriangles.size(); i++)
  {
    Local<Array> tempArray = Array::New(isolate, baseTriangles[i].size());
    for (uint32_t j = 0; j < baseTriangles[i].size(); j++)
    {
      tempArray->Set(j, Number::New(isolate, baseTriangles[i][j]));
    }
    returnArrayJS->Set(i, tempArray);
  }

  std::cout << " --------------------------------------------------------------------\n";
  std::cout << "Bye Bye\n";
  std::cout << " --------------------------------------------------------------------\n";
  args.GetReturnValue().Set(returnArrayJS);
}

void Init(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "triangular", Triangular);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
