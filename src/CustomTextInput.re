[@react.component]
let make =
    (
      ~label: string,
      ~value: string,
      ~onChange: ReactEvent.Form.t => unit,
      ~type_: option(string)=?,
      ~required: option(bool)=?,
      ~maxLength: option(int)=?,
    ) => {
  <div style={ReactDOMRe.Style.make(~marginTop="5px", ())}>
    <label> {(label ++ ": ")->React.string} </label>
    <input name=label ?type_ ?required ?maxLength value onChange />
  </div>;
};