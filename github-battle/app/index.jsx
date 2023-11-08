import * as React from "react"; // from the library we installed using `npm install react`
import * as ReactDOM from "react-dom/client"; // ^ // react dom lets us initialze our application on either client or server side
import "./index.css"; // make it so our css gets applied to our application
import Popular from "./components/Popular";
import Battle from "./components/Battle";

/*
    these components need to:
    1. manage its own state (point of react)
    2. hook into application lifecycle
    3. describe its ui
*/

// create main component of app
class App extends React.Component {
  // in order to have a component describe what its ui looks like, you make a render method on the class
  render() {
    return (
      <div className="light">
        <div className="container">
          <Popular />
        </div>
      </div>
    );
  }
}

const rootElement = document.getElementById("app"); // use the dom API to get the element we want to render to that lives in index.html
const root = ReactDOM.createRoot(rootElement); // what is a root?
root.render(<App />); // initialize our application
