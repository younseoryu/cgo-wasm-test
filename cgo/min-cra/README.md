## Minimum Golang - WASM - CRA binding example (without eject or webpack config)

## How to get here from default CRA

1. Create CRA 
```
npx create-react-app my-app
cd my-app
npm start
```
1. Create "/wasm" folder to compile .wasm file. There, write "main.go", "execute.sh", etc.  
1. Inside "/public" folder, copy wasm_exec.js by running "cp "$(go env GOROOT)/misc/wasm/wasm_exec.js" ." This is a go-wasm-js glue code given from golang. 
1. In header tags of "/public/index.html", copy the code below
```
    <script src="wasm_exec.js"></script>
    <script>
      const go = new Go();
      WebAssembly.instantiateStreaming(fetch("go-wasm.wasm"), go.importObject).then((result) => {
        go.run(result.instance);
      }).catch(alert);
    </script>
```  
1. In /src/App.js copy the code below.

```
    import React from 'react';
    function App() {

    function handleSubmitSayHello(e) {
        e.preventDefault()
        window.sayHelloJS("hi")
    }
    function handleSubmitTest1(e) {
        e.preventDefault()
        window.test1JS("dummy input")
    }
    return (
        <div>
        <div>
            <button type="submit" onClick={(e) => handleSubmitSayHello(e)}>call sayHello() in go</button>
            <br/>
            <button type="submit" onClick={(e) => handleSubmitTest1(e)}>call test1() in go</button>
        </div>
        </div>
    );
    }
    export default App;
```
1. You're all set!