namespace Application
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearSelectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectDescendantsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectAncestorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.expandToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.collapseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorNodesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nodeDetailsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.treeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.processTreesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.concenseTreesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.configurationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.parametersToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.selectDescendantsToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.selectAncestorsToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.collapseToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.expandToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.colorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nodeDetailsToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.clearSelectionToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolsToolStripMenuItem,
            this.treeToolStripMenuItem,
            this.configurationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(623, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.exportToolStripMenuItem,
            this.closeToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.openToolStripMenuItem.Text = "Import...";
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.exportToolStripMenuItem.Text = "Export...";
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clearSelectionToolStripMenuItem,
            this.selectDescendantsToolStripMenuItem,
            this.selectAncestorsToolStripMenuItem,
            this.expandToolStripMenuItem,
            this.collapseToolStripMenuItem,
            this.colorNodesToolStripMenuItem,
            this.nodeDetailsToolStripMenuItem});
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(85, 20);
            this.toolsToolStripMenuItem.Text = "Visualization";
            // 
            // clearSelectionToolStripMenuItem
            // 
            this.clearSelectionToolStripMenuItem.Name = "clearSelectionToolStripMenuItem";
            this.clearSelectionToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.clearSelectionToolStripMenuItem.Text = "Clear Selection";
            this.clearSelectionToolStripMenuItem.Click += new System.EventHandler(this.clearSelectionToolStripMenuItem_Click);
            // 
            // selectDescendantsToolStripMenuItem
            // 
            this.selectDescendantsToolStripMenuItem.Name = "selectDescendantsToolStripMenuItem";
            this.selectDescendantsToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.selectDescendantsToolStripMenuItem.Text = "Select Descendants";
            this.selectDescendantsToolStripMenuItem.Click += new System.EventHandler(this.selectDescendantsToolStripMenuItem_Click);
            // 
            // selectAncestorsToolStripMenuItem
            // 
            this.selectAncestorsToolStripMenuItem.Name = "selectAncestorsToolStripMenuItem";
            this.selectAncestorsToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.selectAncestorsToolStripMenuItem.Text = "Select Ancestors";
            this.selectAncestorsToolStripMenuItem.Click += new System.EventHandler(this.selectAncestorsToolStripMenuItem_Click);
            // 
            // expandToolStripMenuItem
            // 
            this.expandToolStripMenuItem.Name = "expandToolStripMenuItem";
            this.expandToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.expandToolStripMenuItem.Text = "Expand";
            // 
            // collapseToolStripMenuItem
            // 
            this.collapseToolStripMenuItem.Name = "collapseToolStripMenuItem";
            this.collapseToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.collapseToolStripMenuItem.Text = "Collapse";
            // 
            // colorNodesToolStripMenuItem
            // 
            this.colorNodesToolStripMenuItem.Name = "colorNodesToolStripMenuItem";
            this.colorNodesToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.colorNodesToolStripMenuItem.Text = "Color Nodes...";
            // 
            // nodeDetailsToolStripMenuItem
            // 
            this.nodeDetailsToolStripMenuItem.Name = "nodeDetailsToolStripMenuItem";
            this.nodeDetailsToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.nodeDetailsToolStripMenuItem.Text = "Node Details...";
            this.nodeDetailsToolStripMenuItem.Click += new System.EventHandler(this.nodeDetailsToolStripMenuItem_Click);
            // 
            // treeToolStripMenuItem
            // 
            this.treeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.processTreesToolStripMenuItem,
            this.concenseTreesToolStripMenuItem});
            this.treeToolStripMenuItem.Name = "treeToolStripMenuItem";
            this.treeToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.treeToolStripMenuItem.Text = "Tools";
            // 
            // processTreesToolStripMenuItem
            // 
            this.processTreesToolStripMenuItem.Name = "processTreesToolStripMenuItem";
            this.processTreesToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.processTreesToolStripMenuItem.Text = "Process Trees...";
            // 
            // concenseTreesToolStripMenuItem
            // 
            this.concenseTreesToolStripMenuItem.Name = "concenseTreesToolStripMenuItem";
            this.concenseTreesToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.concenseTreesToolStripMenuItem.Text = "Concense Trees...";
            // 
            // configurationToolStripMenuItem
            // 
            this.configurationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.parametersToolStripMenuItem,
            this.optionsToolStripMenuItem});
            this.configurationToolStripMenuItem.Name = "configurationToolStripMenuItem";
            this.configurationToolStripMenuItem.Size = new System.Drawing.Size(93, 20);
            this.configurationToolStripMenuItem.Text = "Configuration";
            // 
            // parametersToolStripMenuItem
            // 
            this.parametersToolStripMenuItem.Name = "parametersToolStripMenuItem";
            this.parametersToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.parametersToolStripMenuItem.Text = "Parameters...";
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.optionsToolStripMenuItem.Text = "Options...";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 27);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(594, 395);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectDescendantsToolStripMenuItem1,
            this.selectAncestorsToolStripMenuItem1,
            this.clearSelectionToolStripMenuItem1,
            this.collapseToolStripMenuItem1,
            this.expandToolStripMenuItem1,
            this.colorToolStripMenuItem,
            this.nodeDetailsToolStripMenuItem1});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(176, 180);
            // 
            // selectDescendantsToolStripMenuItem1
            // 
            this.selectDescendantsToolStripMenuItem1.Name = "selectDescendantsToolStripMenuItem1";
            this.selectDescendantsToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.selectDescendantsToolStripMenuItem1.Text = "Select Descendants";
            this.selectDescendantsToolStripMenuItem1.Click += new System.EventHandler(this.selectDescendantsToolStripMenuItem1_Click);
            // 
            // selectAncestorsToolStripMenuItem1
            // 
            this.selectAncestorsToolStripMenuItem1.Name = "selectAncestorsToolStripMenuItem1";
            this.selectAncestorsToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.selectAncestorsToolStripMenuItem1.Text = "Select Ancestors";
            this.selectAncestorsToolStripMenuItem1.Click += new System.EventHandler(this.selectAncestorsToolStripMenuItem1_Click);
            // 
            // collapseToolStripMenuItem1
            // 
            this.collapseToolStripMenuItem1.Name = "collapseToolStripMenuItem1";
            this.collapseToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.collapseToolStripMenuItem1.Text = "Collapse";
            // 
            // expandToolStripMenuItem1
            // 
            this.expandToolStripMenuItem1.Name = "expandToolStripMenuItem1";
            this.expandToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.expandToolStripMenuItem1.Text = "Expand";
            // 
            // colorToolStripMenuItem
            // 
            this.colorToolStripMenuItem.Name = "colorToolStripMenuItem";
            this.colorToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.colorToolStripMenuItem.Text = "Color...";
            // 
            // nodeDetailsToolStripMenuItem1
            // 
            this.nodeDetailsToolStripMenuItem1.Name = "nodeDetailsToolStripMenuItem1";
            this.nodeDetailsToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.nodeDetailsToolStripMenuItem1.Text = "Node Details...";
            this.nodeDetailsToolStripMenuItem1.Click += new System.EventHandler(this.nodeDetailsToolStripMenuItem1_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Location = new System.Drawing.Point(449, 211);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(34, 40);
            this.pictureBox2.TabIndex = 2;
            this.pictureBox2.TabStop = false;
            // 
            // clearSelectionToolStripMenuItem1
            // 
            this.clearSelectionToolStripMenuItem1.Name = "clearSelectionToolStripMenuItem1";
            this.clearSelectionToolStripMenuItem1.Size = new System.Drawing.Size(175, 22);
            this.clearSelectionToolStripMenuItem1.Text = "Clear Selection";
            this.clearSelectionToolStripMenuItem1.Click += new System.EventHandler(this.clearSelectionToolStripMenuItem1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 434);
            this.ContextMenuStrip = this.contextMenuStrip1;
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Phyloloc";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearSelectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectDescendantsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectAncestorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem expandToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem collapseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem colorNodesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nodeDetailsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem treeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem processTreesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem concenseTreesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem configurationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem parametersToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem selectDescendantsToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem selectAncestorsToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem collapseToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem expandToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem colorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nodeDetailsToolStripMenuItem1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.ToolStripMenuItem clearSelectionToolStripMenuItem1;
    }
}

