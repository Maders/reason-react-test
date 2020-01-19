[@react.component]
let make = (~gateway: Types.gateway, ~onClick) => {
  <div
    key={gateway.id}
    style={ReactDOMRe.Style.make(
      ~border="1px solid #999",
      ~padding="5px",
      ~margin="5px",
      (),
    )}>
    <div> "id: "->React.string {gateway.id}->React.string </div>
    <div> "username: "->React.string {gateway.username}->React.string </div>
    <div>
      "amount: "->React.string
      {gateway.amount->string_of_int->React.string}
    </div>
    <div>
      "type: "->React.string
      <strong> gateway._type->React.string </strong>
    </div>
    <div> "gateway name: "->React.string gateway.gatewayName->React.string </div>
    <div> "from: "->React.string gateway.from->React.string </div>
    <div>
      <a href="#" onClick={onClick(gateway.id)}> "Remove"->React.string </a>
    </div>
  </div>;
};