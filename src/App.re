[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    {switch (url.path) {
     | ["register"] => <Register />
     | ["transaction"] => <Transactions />
     | [] => <Main />
     | _ => <NotFound />
     }}
  </div>;
};