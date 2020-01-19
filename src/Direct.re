[@react.component]
let make = (~direct: Types.direct, ~onClick) => {
  <div
    key={direct.id}
    style={ReactDOMRe.Style.make(
      ~border="1px solid #444",
      ~padding="5px",
      ~margin="5px",
      (),
    )}>
    <div> "id: "->React.string {direct.id}->React.string </div>
    <div> "username: "->React.string {direct.username}->React.string </div>
    <div>
      "amount: "->React.string
      {direct.amount->string_of_int->React.string}
    </div>
    <div>
      "type: "->React.string
      <strong> direct._type->React.string </strong>
    </div>
    <div> "from: "->React.string direct.from->React.string </div>
    <div> "to: "->React.string direct._to->React.string </div>
    <div>
      <a href="#" onClick={onClick(direct.id)}> "Remove"->React.string </a>
    </div>
  </div>;
};