[@react.component]
let make = (~loading: bool) =>
  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexDirection="column",
      (),
    )}>
    {loading
       ? <>
           <img src="/src/assets/loading.gif" />
           <small> "Loading..."->React.string </small>
         </>
       : React.null}
  </div>;