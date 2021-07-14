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
