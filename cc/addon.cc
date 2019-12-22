// addon.cc
#include <node.h>
#include <v8.h>
#include "triangular.h"
#include <vector>
#include <array>

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

// coordinate unpackCoordinates(Isolate *Isolate, const v8::FunctionCallbackInfo<Value> &args)
// {
//   Handle<Array> coordArray = Handle<Array>::Cast(args[0]);
//   vector<vector<double> > coordinates;

//   for (int i = 0; i < coordArray->Length(); i++)
//   {
//     coordinates.push_back(Handle<Array>::Cast(coordArray->Get(i)));
//   }
//   return coordinates;
// }


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



  Delaunay::triangulate(arrayCC);
  


  //////////////////////////////////////////////////////////////////////////////////////////
  Local<Array> returnArrayJS = Array::New(isolate, arrayJS->Length());
  for (uint32_t i = 0; i < arrayCC.size(); i++)
  {
    Local<Array> tempArray = Array::New(isolate, arrayCC[i].size());
    for (uint32_t j = 0; j < arrayCC[i].size(); j++)
    {
      tempArray->Set(j, Number::New(isolate, arrayCC[i][j]));
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
