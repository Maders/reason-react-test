[@react.component]
let make = (~gift: Types.gift, ~onClick) => {
  <div
    key={gift.id}
    style={ReactDOMRe.Style.make(
      ~border="1px solid #000",
      ~padding="5px",
      ~margin="5px",
      (),
    )}>
    <div> "id: "->React.string {gift.id}->React.string </div>
    <div> "username: "->React.string {gift.username}->React.string </div>
    <div>
      "amount: "->React.string
      {gift.amount->string_of_int->React.string}
    </div>
    <div>
      "type: "->React.string
      <strong> gift._type->React.string </strong>
    </div>
    <div>
      <a href="#" onClick={onClick(gift.id)}> "Remove"->React.string </a>
    </div>
  </div>;
};