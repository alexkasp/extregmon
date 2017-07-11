using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.ViewModel
{
    class commandRule: INotifyPropertyChanged
    {
        public string cmname { get; set; }
        public string cmtext { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        public commandRule(string nameval, string textval)
        {
            cmname = nameval;
            cmtext = textval;
        }
        private void RaisePropertyChanged(string property)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(property));
            }
        }

        public override string ToString()
        {
            return cmname;
        }
    }
}
