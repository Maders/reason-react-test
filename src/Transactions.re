type transAction =
  | Add(option(list(Types.transactionType)))
  | Remove(string);

type stateShape = option(list(Types.transactionType));

[@react.component]
let make = () => {
  let reducer = (state: stateShape, action: transAction) => {
    switch (action) {
    | Add(data) => data
    | Remove(tranID) =>
      switch (state) {
      | Some(fstate) =>
        Some(
          fstate
          |> List.filter(trans => {
               switch (trans) {
               | Types.Gift(gp) => gp.id !== tranID
               | Types.Gateway(foo) => foo.id !== tranID
               | Types.Direct(abc) => abc.id !== tranID
               }
             }),
        )
      | None => state
      }
    };
  };
  let (state, dispatch) = React.useReducer(reducer, None);
  let (loading, setLoading) = React.useState(() => true);
  let handleRemoveClick = (id: string, _) => {
    Js.Promise.(
      Fetch.fetchWithInit(
        "http://jobs.skul.io/api/transactions/" ++ id,
        Fetch.RequestInit.make(~method_=Delete, ~credentials=Include, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(_ => {
           dispatch(Remove(id));
           Js.Promise.resolve();
         })
      |> catch(_ => {Js.Promise.resolve()})
      |> ignore
    );
  };

  React.useEffect0(() => {
    Js.Promise.(
      Fetch.fetchWithInit(
        "http://jobs.skul.io/api/transactions",
        Fetch.RequestInit.make(~credentials=Include, ()),
      )
      |> then_(Fetch.Response.json)
      |> then_(json => {
           Some(json |> Types.Decode.all |> Array.to_list)->Add->dispatch;
           setLoading((_)=> false)
           Js.Promise.resolve();
         })
      |> catch(_ => {
            setLoading((_)=> false);
           "/register"->ReasonReactRouter.replace;
           Js.Promise.resolve();
         })
      |> ignore
    );
    None;
  });
  <>
    <h3> "Transcation List:"->React.string </h3>
    <Indicator loading />
    {switch (state) {
     | None => React.null
     | Some(data) =>
       <div
         style={ReactDOMRe.Style.make(
           ~width="80vw",
           ~height="100vh",
           ~display="flex",
           ~flexDirection="row",
           ~flexWrap="wrap",
           ~justifyContent="space-between",
           ~alignItems="baseline",
           (),
         )}>
         {Belt.List.map(data, transaction =>
            switch (transaction) {
            | Types.Gift(gift) =>
              <Gift onClick=handleRemoveClick gift key={gift.id} />
            | Types.Gateway(gateway) =>
              <Gateway onClick=handleRemoveClick gateway key={gateway.id} />
            | Types.Direct(direct) =>
              <Direct onClick=handleRemoveClick direct key={direct.id} />
            }
          )
          |> Array.of_list
          |> React.array}
       </div>
     }}
  </>;
};