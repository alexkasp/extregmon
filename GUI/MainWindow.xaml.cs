using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GUI.ViewModel;
namespace GUI
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        CommandViewModel cvm;
        ServerViewModel svm;
      

        public MainWindow()
        {
            InitializeComponent();

           

        }

        private bool connect(ref ExtregClient erc,string ipaddr,ref string message)
        {
            if (!erc.connect(ipaddr, ref message))
            {
                return false;

            }
            if (erc.recvAnswer(ref message))
               return true;
            return false;
        }

        private bool RunCommand(ref ExtregClient erc,ref Paragraph myparagraph,string command)
        {
            
            List<string> answerList;
            
            if (erc.RunCommand(command, out answerList))
            {
                foreach(string line in answerList)
                {
                    myparagraph.Inlines.Add(line+"\n");
                }

            }
         
            return true;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //  ServerViewModel srv = new ServerViewModel();

            //System.Windows.Data.CollectionViewSource serverViewModelViewSource = ((System.Windows.Data.CollectionViewSource)(this.FindResource("serverViewModelViewSource")));
            // Загрузите данные, установив свойство CollectionViewSource.Source:
            //serverViewModelViewSource.Source = srv;
            cvm = (CommandViewModel)this.Resources["CommandsList"];
            svm = (ServerViewModel)this.Resources["ServersList"];
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            string answer = "";
            
       

      //  richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
            
           
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
/*
            string command = cvm.fomratSelectedCmd(textBox1.Text,textBox2.Text);
            Paragraph myparagraph = new Paragraph();
            ExtregClient selected;
            svm.getSelected(out selected);

          
            RunCommand(ref selected, ref myparagraph, command);

            richTextBox.Document.Blocks.Add(myparagraph);*/
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
          //  richTextBox.Document.Blocks.Clear();
        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
 