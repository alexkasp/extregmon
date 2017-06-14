using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI
{
    class ServerViewModel
    {
        private String connected = "construct inited";

        public String connectedProp
        {
            get { return this.connected; }
            set { connected = value; }
        }
    }
}
