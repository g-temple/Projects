import * as React from "react";
import PropTypes from "prop-types";
import { fetchPopularRepos } from "../utils/api";
import Table from "./Table";

// function responsible for rendering a piece of the nav bar
// function onUpdateLanguage - sets the state to the updated language
// returns a renderable list
function LanguagesNav({ selected, onUpdateLanguage }) {
  const languages = ["All", "JavaScript", "Ruby", "Java", "CSS", "Python"];

  return (
    <select
      onChange={(e) => onUpdateLanguage(e.target.value)}
      selected={selected}
    >
      {languages.map((language) => (
        <option key={language} value={language}>
          {language}
        </option>
      ))}
    </select>
  );
}

LanguagesNav.propTypes = {
  selected: PropTypes.string.isRequired,
  onUpdateLanguage: PropTypes.func.isRequired,
};

export default class Popular extends React.Component {
  // create a constructor to initialize the state
  // while we have access to a props object, it does not have anything because when it is called in index.js, we dont pass anything to it
  constructor(props) {
    super(props);

    // this is how to declare a state in react
    this.state = {
      selectedLanguage: "All",
      repos: null,
      error: null,
    };

    // whenever you make a class that has functions, you need to include this boilerplate so "this" is properly bound
    //you could also use an arrow function and not include this, but arrow functions are kinda hard
    this.updateLanguage = this.updateLanguage.bind(this);
  }

  componentDidMount() {
    // when the component mounts, this method is called, and we use it to update the ui based on the selected langauge
    this.updateLanguage(this.state.selectedLanguage);
  }

  updateLanguage(selectedLanguage) {
    // when using set state, you typically need to create another object to merge into the current state
    this.setState({
      selectedLanguage,
      error: null,
    });

    fetchPopularRepos(selectedLanguage) // after getting the repos, set the state to include such repos
      .then((repos) =>
        this.setState({
          repos,
          error: null,
        })
      )
      .catch((error) => {
        // catch an errors, display them, and update the state to reflect the error
        console.warn("Error fetching repos");

        this.setState({
          error: "There was an error fetching the repositories",
        });
      });
  }

  render() {
    // destructure the current selected language from the state
    const { selectedLanguage, repos, error } = this.state;

    // return jsx to be rendered
    return (
      <main className="Stack main-stack animate-in">
        <div className="split">
          <h1>Popular</h1>
          <LanguagesNav
            selected={selectedLanguage} // these are the props that get passed somewhat like params to the LanguagesNav function
            onUpdateLanguage={this.updateLanguage} // since they evaluate to something, they need to be wrappe in {}
          />
        </div>

        {error && <p className="text-center error">{error}</p>}

        {repos && <Table repos={repos} />}
      </main>
    );
  }
}
