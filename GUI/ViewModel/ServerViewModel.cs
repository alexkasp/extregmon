using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI.Model;

namespace GUI.ViewModel
{
    class ServerViewModel
    {

        Server srv = new Server();

        public string Connected
        {
            get { return srv.connectedProp; }
            set { srv.connectedProp = value; }
        }

      
    }
}
