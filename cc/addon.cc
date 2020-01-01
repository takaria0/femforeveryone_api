// addon.cc
#include <node.h>
#include <v8.h>
#include <vector>
#include <array>
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
  Isolate *isolate = args.GetIsolate();

  Local<Object> objJS = Local<Object>::Cast(args[0]);
  Local<Array> arrayJS = Local<Array>::Cast(objJS->Get(String::NewFromUtf8(isolate, "geometries")));

  vector<vector<double>> arrayCC(arrayJS->Length(), vector<double>(2, 0));
  for (uint32_t i=0; i<arrayJS->Length(); i++)
  {
    Local<Array> innerArrayJS = Local<Array>::Cast(arrayJS->Get(i).As<Array>());
    for (uint32_t j = 0; j <innerArrayJS->Length(); j++)
    {
      arrayCC[i][j] = innerArrayJS->Get(j).As<Number>()->Value();
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////
  Delaunay tri;
  TwoDimensionTriangularFiniteElementMethod fem;
  vector<vector<double>> triangles;
  tri.triangulate(arrayCC, 50);
  triangles = tri.getTriangles();
  //////////////////////////////////////////////////////////////////////////////////////////
  Local<Array> returnArrayJS = Array::New(isolate, triangles.size());
  for (uint32_t i = 0; i < triangles.size(); i++)
  {
    Local<Array> tempArray = Array::New(isolate, triangles[i].size());
    for (uint32_t j = 0; j < triangles[i].size(); j++)
    {
      tempArray->Set(j, Number::New(isolate, triangles[i][j]));
    }
    returnArrayJS->Set(i, tempArray);
  }

  args.GetReturnValue().Set(returnArrayJS);
}

void Init(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "triangular", Triangular);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
