namespace cpp ThriftyGramophone

/**
* enum State {
*  PLAYING = 1,
*  PAUSED = 2,
*  STOPPED = 3
*}
*
*struct Status{
*  1:State state,
*  2:string URI,
*  3:i32 time
*}
*/

service ThriftyGramophone
{
  i32 play(1:string uri),
/**
*  Status status(),
*  i32 register_client(1:string id, 2:Client client),
*  i32 unregister_client(1:string id)
*/
}