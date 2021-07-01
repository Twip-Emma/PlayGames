using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class UImanager : MonoBehaviour
{
    public static UImanager instance{get;private set;}

    void Awake(){
        instance = this;
    }
    
    public Image healthBar;

    public Text bulletCountText;

    ///<param name = "curAmount"></param>
    ///<param name = "maxAmount"></param>
    public void UpdateHealthBar(int curAmount, int maxAmount){

        healthBar.fillAmount = (float)curAmount / (float)maxAmount;
    }

    //更新子弹文本显示
    public void UpdateBulletCount(int curAmount,int maxAmount){
        bulletCountText.text = curAmount.ToString() + "/" + maxAmount.ToString();
    }
}
