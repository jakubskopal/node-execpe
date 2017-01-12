#include <cstdio>
#include <stdlib.h>
#include <string.h>
#if defined(__NODE_V0_11_OR_12__) || defined(__NODE_GE_V4__)
#include <fcntl.h>
#endif

//#ifdef __POSIX__
#include <unistd.h>
/*#else
#include <process.h>
#endif*/

#include <nan.h>


using v8::Array;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Integer;
using v8::Local;
using v8::Object;
using v8::String;


static int clear_cloexec (int desc)
{
    int flags = fcntl (desc, F_GETFD, 0);
    if (flags <  0)
        return flags; //return if reading failed

    flags &= ~FD_CLOEXEC; //clear FD_CLOEXEC bit
    return fcntl (desc, F_SETFD, flags);
}

static int do_exec(char *argv[], char *env[])
{
        clear_cloexec(0); //stdin
        clear_cloexec(1); //stdout
        clear_cloexec(2); //stderr
        return execvpe(argv[0], argv, env);
}

NAN_METHOD(execpe) {
    /*
     * Interface changed to be:
     *   1st argument is a path
     *   2nd argument array of arguments
     *   3rd argument map of environment
     *
     */

    if ( 3 != info.Length()
         || !info[0]->IsString()
         || !info[1]->IsArray()
         || !info[2]->IsArray()) {
        return Nan::ThrowTypeError("execpe: invalid arguments");
    }

    String::Utf8Value file(info[0]->ToString());

    int i;

    // Copy second argument info[1] into a c-string array called argv.
    // The array must be null terminated, and the first element must be
    // the name of the executable -- hence the complication.
    Local<Array> argv_handle = Local<Array>::Cast(info[1]);
    int argc = argv_handle->Length();
    int argv_length = argc + 1 + 1;
    char **argv = new char*[argv_length]; // heap allocated to detect errors
    argv[0] = strdup(*file); // + 1 for file
    argv[argv_length-1] = NULL;  // + 1 for NULL;
    for (i = 0; i < argc; i++) {
        String::Utf8Value arg(argv_handle->Get(Integer::New(info.GetIsolate(), i))->ToString());
        argv[i+1] = strdup(*arg);
    }

    // Copy third argument, info[2], into a c-string array called env.
    Local<Array> env_handle = Local<Array>::Cast(info[2]);
    int envc = env_handle->Length();
    char **env = new char*[envc+1]; // heap allocated to detect errors
    env[envc] = NULL;
    for (int i = 0; i < envc; i++) {
        String::Utf8Value pair(env_handle->Get(Integer::New(info.GetIsolate(), i))->ToString());
        env[i] = strdup(*pair);
    }

    int err = do_exec(argv, env);

    for (int i = 0; i < argv_length - 1; i++)
        free(argv[i]);
    for (int i = 0; i < envc; i++)
        free(env[i]);
    delete [] argv;
    delete [] env;

    info.GetReturnValue().Set(Integer::New(info.GetIsolate(), err));
}


#define EXPORT(name, symbol) exports->Set( \
  Nan::New<String>(name).ToLocalChecked(), \
  Nan::New<FunctionTemplate>(symbol)->GetFunction() \
)

void init (Handle<Object> exports) {
    EXPORT("execpe", execpe);
}

NODE_MODULE(execpe, init);
