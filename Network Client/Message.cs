namespace Network_Client
{
    class Message
    {
        public enum Type
        {
            authQuery = 1,
            authRequest,
            authFailed,
            welcome,
            welcomeReceived,
            chat,
            spawnPlayer,
            playerPosition,
            playerRotation
        }


    }
}
