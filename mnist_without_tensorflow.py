#!/usr/bin/env python
# coding: utf-8

# In[3]:


import numpy as np


# In[4]:


import pandas as pd


# In[ ]:





# In[5]:


import scipy.special


# In[6]:


import matplotlib.pyplot


# In[7]:


get_ipython().run_line_magic('matplotlib', 'inline')


# In[8]:


class mnist:
    def init(self,inodes,hnodes,onodes,learnrate):
        self.inputnodes=inodes
        self.outputnodes=onodes
        self.hiddennodes=hnodes
        self.lr=learnrate
        self.wih=(np.random.rand(self.hiddennodes,self.inputnodes)-.5)
        self.who=(np.random.rand(self.outputnodes,self.hiddennodes)-.5)
        self.act=lambda x:scipy.special.expit(x)
        pass
    def train(self,inputlist,targetlist):
        input=np.array(inputlist,ndmin=2).T
        target=np.array(targetlist,ndmin=2).T
        hi=np.dot(self.wih,input)
        ho=self.act(hi)
        fi=np.dot(self.who,ho)
        fo=self.act(fi)
        error=target-fo
        eh=np.dot(self.who.T,error)
        self.who+=self.lr*np.dot((error*fo*(1-fo)),np.transpose(ho))
        self.wih+=self.lr*np.dot((eh*ho*(1-ho)),np.transpose(input))
        pass
    def query(self,inputlist):
        input=np.array(inputlist,ndmin=2).T
        hi=np.dot(self.wih,input)
        ho=self.act(hi)
        fi=np.dot(self.who,ho)
        fo=self.act(fi)
        return fo
    
        
        
        


# In[9]:


inputnodes=784
hiddennodes=200
output=10
learningrate=0.1
n=mnist()


# In[10]:


n.init(inputnodes,hiddennodes,output,learningrate)


# In[9]:


file=open("C:/Users/Asus/Downloads/mnist.csv",'r')
data=file.readlines()
file.close()


# In[ ]:





# In[34]:


for i in range(1,6):
    for record in dat:
        all_values=record.split(',')
        arr=(np.asfarray(all_values[1:])/255.0*0.99)+0.01
        target=np.zeros(output)+0.01
        target[int (all_values[0])]=0.99
        n.train(arr,target)
        pass
    pass
    
    
   


# In[14]:


dat=pd.read_csv('C:/Users/Asus/Downloads/test.csv')


# In[ ]:





# In[15]:


dat


# In[32]:


dat=dat[1:]


# In[12]:


filed.close()


# In[20]:


first=dat[2].split(',')


# In[21]:


fir=(np.asfarray(first)/255.0*0.99)+0.01


# In[22]:


n.query(fir)


# In[23]:


fir=fir.reshape(28,28)
matplotlib.pyplot.imshow(fir,cmap='Greys',interpolation='none')


# In[ ]:


score=[]
predictions=[]
for record in dat:
    first=record.split(',')
    corr=int(first[0])
    print(corr)
    fir=(np.asfarray(first[1:])/255.0*0.99)+0.01
    final=n.query(fir)
    fin=np.argmax(final)
    predictions.append(fin)
    
    print(fin)
    if(fin==corr):
        score.append(1)
    else:
        score.append(0)
        pass

sc_array=np.asarray(score)
per=sc_array.sum()/sc_array.size

    
        
    
    
    


# In[ ]:


per


# In[ ]:


result=np.asarray(predictions)
print(result)
submissions = pd.DataFrame({"ImageId": list(range(1,len(result)+1)),
    "Label": result})
submissions.to_csv("DR.csv", index=False, header=True)


# In[ ]:


submissions


# In[ ]:




