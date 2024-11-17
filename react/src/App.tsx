import Router from "./components/Router";
import { LogInProvider } from "./components/logincontext";



function App() {
  return (
    <LogInProvider>
      <div>
        <Router/>
      </div>
    </LogInProvider>
  );
}

export default App;
