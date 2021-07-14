## Minimum Golang - WASM - CRA binding example (without eject or webpack config)

## How to get here from default CRA

1. Create "/wasm" folder. There, create a file "main.go" and "execute.sh" 
1. Inside "/public" folder, copy wasm_exec.js by running "cp "$(go env GOROOT)/misc/wasm/wasm_exec.js" ."
1. In header tags of "/public/index.html", copy the code below
```
<script src="wasm_exec.js"></script>
    <script>
      const go = new Go();
      WebAssembly.instantiateStreaming(fetch("go_build_colorate_js.wasm"), go.importObject).then((result) => {
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
  return (
    <div>
      <div>
        <button type="submit" onClick={(e) => handleSubmitSayHello(e)}>call sayHello() in go</button>
      </div>
    </div>
  );
}
export default App;

```