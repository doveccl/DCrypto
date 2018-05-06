#include <node.h>
#include "lib/dcrypto.h"

using namespace v8;

void Enc(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong number of arguments")
    ));
    return ;
  }

  if (!args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments")
    ));
    return ;
  }

  if (args.Length() >= 3) {
    String::Utf8Value _ab(args[2]->ToString());
    DCrypto::enc_a = ((char *)*_ab)[0];
    DCrypto::enc_b = ((char *)*_ab)[1];
  } else {
    DCrypto::enc_a = 'a';
    DCrypto::enc_b = 'b';
  }

  String::Utf8Value _str(args[0]->ToString());
  const char *str = *_str;
  const int seed = args[1]->IntegerValue();

  const char *rstr = DCrypto::dc_encrypt(str, seed);
  if (rstr == NULL) {
    isolate->ThrowException(Exception::Error(
      String::NewFromUtf8(isolate, "Encrypt error")
    ));
  } else {
    MaybeLocal<String> res(String::NewFromOneByte(
      isolate, (const uint8_t *)rstr,
      NewStringType::kNormal, strlen(rstr)
    ));
    args.GetReturnValue().Set(res.ToLocalChecked());
  }
}

void Dec(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong number of arguments")
    ));
    return ;
  }

  if (!args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments")
    ));
    return ;
  }

  if (args.Length() >= 3) {
    String::Utf8Value _ab(args[2]->ToString());
    DCrypto::enc_a = ((char *)*_ab)[0];
    DCrypto::enc_b = ((char *)*_ab)[1];
  } else {
    DCrypto::enc_a = 'a';
    DCrypto::enc_b = 'b';
  }

  Local<String> s(args[0]->ToString());
  char *str = new char[2 * s->Length()];
  s->WriteOneByte((uint8_t *)str);

  const int seed = args[1]->IntegerValue();

  const char *rstr = DCrypto::dc_decrypt(str, seed);
  if (rstr == NULL) {
    isolate->ThrowException(Exception::Error(
      String::NewFromUtf8(isolate, "Decrypt error")
    ));
  } else {
    Local<String> res = String::NewFromUtf8(isolate, rstr);
    args.GetReturnValue().Set(res);
  }
}

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "encrypt", Enc);
  NODE_SET_METHOD(exports, "decrypt", Dec);
}

NODE_MODULE(dcrypto, Init)
