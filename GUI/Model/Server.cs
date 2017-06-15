using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace GUI.Model
{
    class Server : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private String connected = "construct inited";

        public String connectedProp
        {
            get { return this.connected; }
            set
            {
                connected = value;
                RaisePropertyChanged("connected");
            }
        }
       

        private void RaisePropertyChanged(string property)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(property));
            }
        }
    }
}

