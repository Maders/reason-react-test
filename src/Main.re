[@react.component]
let make = () => {
  let (loading, setLoading) = React.useState(() => true);

  React.useEffect0(() => {
    Js.Promise.(
      Fetch.fetchWithInit(
        "http://jobs.skul.io/api/sessions",
        Fetch.RequestInit.make(~credentials=Include, ()),
      )
      |> then_(Fetch.Response.json)
      |> then_(_ => {
           setLoading(_previousState => false);
           "/transaction"->ReasonReactRouter.replace;
           Js.Promise.resolve();
         })
      |> catch(_ => {
           setLoading(_previousState => false);
           "/register"->ReasonReactRouter.replace;
           Js.Promise.resolve();
         })
      |> ignore
    );
    None;
  });

  <Indicator loading /> 
};