type gift = {
  id: string,
  username: string,
  amount: int,
  _type: string,
};

type direct = {
  id: string,
  username: string,
  amount: int,
  from: string,
  _to: string,
  _type: string,
};

type gateway = {
  id: string,
  username: string,
  amount: int,
  from: string,
  gatewayName: string,
  _type: string,
};

type transactionType =
  | Gift(gift)
  | Direct(direct)
  | Gateway(gateway);

type transatctions = option(array(transactionType));

module Decode = {
  let decodeGift = json => {
    Json.Decode.{
      id: json |> field("id", string),
      username: json |> field("username", string),
      amount: json |> field("amount", int),
      _type: json |> field("_type", string),
    };
  };
  let decodeDirect = json => {
    Json.Decode.{
      id: json |> field("id", string),
      username: json |> field("username", string),
      amount: json |> field("amount", int),
      _type: json |> field("_type", string),
      from: json |> field("from", string),
      _to: json |> field("to", string),
    };
  };

  let decodeGateway = json => {
    Json.Decode.{
      id: json |> field("id", string),
      username: json |> field("username", string),
      amount: json |> field("amount", int),
      _type: json |> field("_type", string),
      from: json |> field("from", string),
      gatewayName: json |> field("gatewayName", string),
    };
  };
  let decodeByType =
    Json.Decode.(
      oneOf([
        decodeDirect |> map(x => x->Direct),
        decodeGateway |> map(x => x->Gateway),
        decodeGift |> map(x => x->Gift),
      ])
    );

  let all = Json.Decode.array(decodeByType);
};