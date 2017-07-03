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
        ExtregClient erc1;
        ExtregClient erc2;
        ExtregClient erc3;
        ExtregClient erc4;
        ExtregClient erc5;

        public MainWindow()
        {
            InitializeComponent();
            erc1 = new ExtregClient();
            erc2 = new ExtregClient();
            erc3 = new ExtregClient();
            erc4 = new ExtregClient();
            erc5 = new ExtregClient();
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
            
            string answer = "";
            string proto = "";
            
            if (erc.sendCommand(command, ref answer))
            {
                if (erc.recvAnswer(ref answer))
                {
                    do
                    {
                        if (answer == "finish\0")
                            return true;
                        myparagraph.Inlines.Add(answer + "\n");
                        erc.sendCommand("next", ref proto);

                    } while(erc.recvAnswer(ref answer));
                }
               

            }
            else
            {
                myparagraph.Inlines.Add(answer + "\n");
            }
            myparagraph.Inlines.Add(answer + "\n");

            return true;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
          //  ServerViewModel srv = new ServerViewModel();

            //System.Windows.Data.CollectionViewSource serverViewModelViewSource = ((System.Windows.Data.CollectionViewSource)(this.FindResource("serverViewModelViewSource")));
            // Загрузите данные, установив свойство CollectionViewSource.Source:
            //serverViewModelViewSource.Source = srv;
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            string answer = "";
            if(comboBox.SelectedIndex==0)
            {
                connect(ref erc1,"212.193.100.96",ref answer);
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
                connect(ref erc2, "212.193.100.97", ref answer);
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
                connect(ref erc3, "212.193.100.94", ref answer);
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
                connect(ref erc4, "212.193.100.95", ref answer);
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
                connect(ref erc5, "212.193.100.65", ref answer);
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
            }
            else
            {
                 if (comboBox.SelectedIndex == 1)
                    connect(ref erc1, comboBox.Text, ref answer);
                else if (comboBox.SelectedIndex == 2)
                    connect(ref erc2, comboBox.Text, ref answer);
                else if (comboBox.SelectedIndex == 3)
                    connect(ref erc3, comboBox.Text, ref answer);
                else if (comboBox.SelectedIndex == 4)
                    connect(ref erc4, comboBox.Text, ref answer);
                else if (comboBox.SelectedIndex == 5)
                    connect(ref erc5, comboBox.Text, ref answer);


                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
            }
           
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            
            string command = textBox.Text+textBox1.Text+ "\",\"RequestTime\":\""+textBox2.Text+"\"}";
            Paragraph myparagraph = new Paragraph();

            if (comboBox1.SelectedIndex==0)
            {
                RunCommand(ref erc1,ref myparagraph, command);
                RunCommand(ref erc2, ref myparagraph, command);
                RunCommand(ref erc3, ref myparagraph, command);
                RunCommand(ref erc4, ref myparagraph, command);
                RunCommand(ref erc5, ref myparagraph, command);

            }
           else if (comboBox1.SelectedIndex == 1)
                RunCommand(ref erc1, ref myparagraph, command);
            else if (comboBox1.SelectedIndex == 2)
                RunCommand(ref erc2, ref myparagraph, command);
            else if (comboBox1.SelectedIndex == 3)
                RunCommand(ref erc3, ref myparagraph, command);
            else if (comboBox1.SelectedIndex == 4)
                RunCommand(ref erc4, ref myparagraph, command);
            else if (comboBox1.SelectedIndex == 5)
                RunCommand(ref erc5, ref myparagraph, command);

            richTextBox.Document.Blocks.Add(myparagraph);
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            richTextBox.Document.Blocks.Clear();
        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
 